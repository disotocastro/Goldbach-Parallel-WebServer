// Copyright 2024 Diego Soto, Migueledo Nuñez, William Moraes
// Universidad de Costa Rica. CC BY 4.0

#include "FactWebApp.hpp"

#include <algorithm>
#include <cassert>
#include <iostream>
#include <regex>
#include <stdexcept>
#include <string>
#include <unordered_map>


FactWebApp::FactWebApp() {}

FactWebApp::~FactWebApp() {}

void FactWebApp::start() {
  // TODO(you): Start producers, consumers, assemblers...
  this->key = "fact";
  this->uriAnalizer = new FactUriAnalizer();
  this->uriAnalizer->createOwnQueue();

  // Cola de entrada
  this->entranceQueue = this->uriAnalizer->getConsumingQueue();
  this->uriAnalizer->startThread();
}

void FactWebApp::stop() {
  // TODO(you): Stop producers, consumers, assemblers...
}

