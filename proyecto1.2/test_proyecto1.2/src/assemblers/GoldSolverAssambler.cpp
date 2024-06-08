#include "GoldSolverAssambler.hpp"

#include "GoldSolver.hpp"
#include "numbers.hpp"

solverAssambler::solverAssambler(Queue<Numbers_t*>* Numbers_t_queue,
                                 Queue<Numbers_t*>* numbers_t_queue_resolved) {
  this->setConsumingQueue(Numbers_t_queue);
  this->setProducingQueue(numbers_t_queue_resolved);
}

void solverAssambler::consume(Numbers_t* number) {
  GoldSolver solver;
  solver.resolveGoldbach(number);
  produce(number);
}

int solverAssambler::run() {
  this->consumeForever();
  return EXIT_SUCCESS;
}
