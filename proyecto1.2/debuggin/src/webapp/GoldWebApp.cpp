// Copyright 2021 Jeisson Hidalgo-Cespedes. Universidad de Costa Rica. CC BY 4.0

#include "GoldWebApp.hpp"

#include <Queue.hpp>
#include <algorithm>
#include <cassert>
#include <cstring>
#include <iostream>
#include <regex>
#include <stdexcept>
#include <string>

#include "GoldSolver.hpp"
#include "HttpRequest.hpp"
#include "HttpResponse.hpp"
#include "numbers.hpp"

GoldWebApp::GoldWebApp() {}

GoldWebApp::~GoldWebApp() {}

void GoldWebApp::start() {
  // TODO(you): Start producers, consumers, assemblers...
  this->key = "gold";

  // Initialize the components
  this->uriAnalizer = new GoldUriAnalizer();
  this->sortAssembler = new GoldSortAssembler();
  this->buildHTML = new GoldHTML();

  // // Initialize the components
  this->uriAnalizer->createOwnQueue();
  this->sortAssembler->createOwnQueue();
  this->buildHTML->createOwnQueue();

  this->vectorSolverAssemblers.resize(this->maxSolvers);
  for (int64_t i = 0; i < this->maxSolvers; i++) {
    this->vectorSolverAssemblers[i] = new GoldSolverAssembler();
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

  this->entranceQueue = this->uriAnalizer->getConsumingQueue();
  this->uriAnalizer->setProducingQueue(
      this->vectorSolverAssemblers[0]->getConsumingQueue());

  // Set the queue chain for processing

  this->sortAssembler->setProducingQueue(this->buildHTML->getConsumingQueue());
  // Start each component in its own thread

  this->uriAnalizer->startThread();
  this->sortAssembler->startThread();
  this->buildHTML->startThread();
}

void GoldWebApp::stop() {
  // TODO(you): Stop producers, consumers, assemblers...
}
