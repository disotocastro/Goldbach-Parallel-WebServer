// Copyright 2024 Diego Soto, Migueledo Nuñez, William Morales
// Universidad de Costa Rica. CC BY 4.0

#include "GoldSolverAssembler.hpp"
#include "numbers.hpp"

int GoldSolverAssembler::run() {
  this->consumeForever();
  return EXIT_SUCCESS;
}

void GoldSolverAssembler::consume(Numbers_t* number) {
  GoldSolver solver;
  solver.resolveGoldbach(number);
  produce(number);
  
}
