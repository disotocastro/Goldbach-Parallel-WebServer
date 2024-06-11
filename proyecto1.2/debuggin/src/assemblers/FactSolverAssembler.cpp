// Copyright 2024 Diego Soto, Migueledo Nuñez, William Morales
// Universidad de Costa Rica. CC BY 4.0

#include "FactSolverAssembler.hpp"

int FactSolverAssembler::run() {
  this->consumeForever();
  return EXIT_SUCCESS;
}

void FactSolverAssembler::consume(FactNumber* data) {
  FactSolver solver = FactSolver();
  data->numbersVector = solver.FactorizeVector(data->numero);
  produce(data);
}
