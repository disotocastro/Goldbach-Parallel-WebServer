// Copyright 2024 Diego Soto, Migueledo Nuñez, William Morales
// Universidad de Costa Rica. CC BY 4.0

#include "FactWebApp.hpp"

#include <algorithm>
#include <cassert>
#include <iostream>
#include <regex>
#include <stdexcept>
#include <string>


#include "FactNumber.hpp"
#include "FactSolverAssembler.hpp"

FactWebApp::FactWebApp() {}

FactWebApp::~FactWebApp() {}

void FactWebApp::start() {
  // TODO(you): Start producers, consumers, assemblers...
  this->key = "fact";

  this->uriAnalizer = new FactUriAnalizer();
  this->solverAssembler = new FactSolverAssembler();
  this->sortAssembler = new FactSortAssembler();
  this->buildHTML = new FactHTML();

  this->uriAnalizer->createOwnQueue();
  this->solverAssembler->createOwnQueue();
  this->sortAssembler->createOwnQueue();
  this->buildHTML->createOwnQueue();
  // Cola de entrada
  this->entranceQueue = this->uriAnalizer->getConsumingQueue();

  this->uriAnalizer->setProducingQueue(
      this->solverAssembler->getConsumingQueue());

  this->solverAssembler->setProducingQueue(
      this->sortAssembler->getConsumingQueue());

  this->sortAssembler->setProducingQueue(this->buildHTML->getConsumingQueue());

  this->solverAssembler->startThread();
  this->uriAnalizer->startThread();
  this->sortAssembler->startThread();
  this->buildHTML->startThread();

}

void FactWebApp::stop() {
  // TODO(you): Stop producers, consumers, assemblers...
}
