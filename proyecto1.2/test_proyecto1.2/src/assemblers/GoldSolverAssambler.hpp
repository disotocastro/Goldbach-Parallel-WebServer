// Copyright 2024 Diego Soto, Migueledo Nuñez, William Moraes
// Universidad de Costa Rica. CC BY 4.0

#ifndef GOLDSOLVERASSAMBLER_HPP
#define GOLDSOLVERASSAMBLER_HPP

#include <vector>

#include "Assembler.hpp"
#include "HttpApp.hpp"
#include "Queue.hpp"
#include "numbers.hpp"

class Solver_Assembler : public Assembler<Numbers_t*, Numbers_t*> {
 public:
  Solver_Assembler();
  explicit Solver_Assembler(Queue<Numbers_t*>* Numbers_t_queue,
                           Queue<Numbers_t*>* numbers_t_queue_resolved);
  int run() override;
  void consume(Numbers_t* number) override;

 protected:
};

#endif  // ANALIZAURI_HPP
