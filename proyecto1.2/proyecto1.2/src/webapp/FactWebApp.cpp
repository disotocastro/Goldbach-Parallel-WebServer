// Copyright 2024 Diego Soto, Migueledo Nuñez, William Morales
// Uniersidad de Costa Rica. CC BY 4.0

#include "FactWebApp.hpp"

#include <algorithm>
#include <cassert>
#include <iostream>
#include <regex>
#include <stdexcept>
#include <string>

FactWebApp::FactWebApp() {}

FactWebApp::~FactWebApp() {}

void FactWebApp::start() {
  // TODO(you): Start producers, consumers, assemblers...
  this->key = "fact";

  // Initialize the components
  this->uriAnalizer = new FactUriAnalizer();
  this->sortAssembler = new FactSortAssembler();
  this->buildHTML = new FactHTML();

  // Initialize the components
  this->uriAnalizer->createOwnQueue();
  this->sortAssembler->createOwnQueue();
  this->buildHTML->createOwnQueue();

  this->vectorSolverAssemblers.resize(this->maxSolvers);
  for (int64_t i = 0; i < this->maxSolvers; i++) {
    this->vectorSolverAssemblers[i] = new FactSolverAssembler();
    if (i == 0) {
      this->vectorSolverAssemblers[i]->createOwnQueue();
    } else {
      this->vectorSolverAssemblers[i]->setConsumingQueue(
          this->vectorSolverAssemblers[0]->getConsumingQueue());
    }
    this->vectorSolverAssemblers[i]->setProducingQueue(
        this->sortAssembler->getConsumingQueue());
    this->vectorSolverAssemblers[i]->startThread();
  }

  // Set the entrance queue for incoming requests
  this->entranceQueue = this->uriAnalizer->getConsumingQueue();
  // Set the queue chain for processing

  this->uriAnalizer->setProducingQueue(
      this->vectorSolverAssemblers[0]->getConsumingQueue());

  this->sortAssembler->setProducingQueue(this->buildHTML->getConsumingQueue());
  // Start each component in its own thread

  this->uriAnalizer->startThread();
  this->sortAssembler->startThread();
  this->buildHTML->startThread();
}

void FactWebApp::stop() {
  // TODO(you): Stop producers, consumers, assemblers...

  this->uriAnalizer->waitToFinish();
  this->sortAssembler->waitToFinish();
  this->buildHTML->waitToFinish();

  for (int64_t i = 0; i < this->maxSolvers; i++) {
    this->vectorSolverAssemblers[i]->waitToFinish();
    delete this->vectorSolverAssemblers[i];
  }

  delete this->uriAnalizer;
  delete this->sortAssembler;
  delete this->buildHTML;
}
