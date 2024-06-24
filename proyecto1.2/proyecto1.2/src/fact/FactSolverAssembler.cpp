// Copyright 2024 Diego Soto, Migueledo Nuñez, William Morales
// Universidad de Costa Rica. CC BY 4.0

#include "FactSolverAssembler.hpp"
#include <iostream>

int FactSolverAssembler::run() {
  this->consumeForever();
  FactNumber temp = FactNumber();
  produce(&temp);

  return EXIT_SUCCESS;
}

void FactSolverAssembler::consume(FactNumber* data) {
  FactSolver solver = FactSolver();
  data->numbersVector = solver.FactorizeVector(data->numero);
  produce(data);
}

void FactSolverAssembler::consumeForever() {
  assert(this->consumingQueue);
  while (true) {
    // Get the next data to consume, or block while queue is empty
    FactNumber* data = this->consumingQueue->dequeue();
    // If data is the stop condition, stop the loop
    if (data->id == 0) {
      break;
    }
    // Process this data
    this->consume(data);
  }
}
