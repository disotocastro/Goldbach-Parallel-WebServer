// Copyright 2024 Diego Soto, Migueledo Nuñez, William Morales
// Universidad de Costa Rica. CC BY 4.0

#include "GoldSolverAssembler.hpp"

int GoldSolverAssembler::run() {
  this->consumeForever();
  Numbers_t temp = Numbers_t();
  produce(&temp);
  return EXIT_SUCCESS;
}

void GoldSolverAssembler::consume(Numbers_t* number) {
  GoldSolver solver;
  solver.resolveGoldbach(number);
  produce(number);
}

void GoldSolverAssembler::consumeForever() {
  assert(this->consumingQueue);
  while (true) {
    // Get the next data to consume, or block while queue is empty
    Numbers_t* data = this->consumingQueue->dequeue();
    // If data is the stop condition, stop the loop
    if (data->id == 0) {
      break;
    }
    // Process this data
    this->consume(data);
  }
}
