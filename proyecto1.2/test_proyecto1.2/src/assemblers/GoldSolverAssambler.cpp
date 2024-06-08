#include "GoldSolverAssambler.hpp"

#include "GoldSolver.hpp"
#include "numbers.hpp"

Gold_Solver_Assembler::Gold_Solver_Assembler(Queue<Numbers_t*>* Numbers_t_queue,
                                 Queue<Numbers_t*>* numbers_t_queue_resolved) {
  this->setConsumingQueue(Numbers_t_queue);
  this->setProducingQueue(numbers_t_queue_resolved);
}

void Gold_Solver_Assembler::consume(Numbers_t* number) {
  GoldSolver solver;
  solver.resolveGoldbach(number);
  produce(number);
}

int Gold_Solver_Assembler::run() {
  this->consumeForever();
  return EXIT_SUCCESS;
}
