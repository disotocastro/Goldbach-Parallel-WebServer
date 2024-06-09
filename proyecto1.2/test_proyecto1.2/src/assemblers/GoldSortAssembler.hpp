// Copyright 2024 Diego Soto, Migueledo Nuñez, William Moraes
// Universidad de Costa Rica. CC BY 4.0

#ifndef GOLDSORTASSEMBLER_HPP
#define GOLDSORTASSEMBLER_HPP

#include <vector>

#include "Assembler.hpp"
#include "HttpApp.hpp"
#include "Queue.hpp"
#include "numbers.hpp"

class Sort_Assembler : public Assembler<Numbers_t*, RequestResolved_t*> {
 public:
  Sort_Assembler();
  explicit Sort_Assembler(Queue<Numbers_t*>* numbers_t_queue_resolved,
                          Queue<RequestResolved_t*>* request_resolved_queue);

  int run() override;
  void consume(Numbers_t* numbers_t_resolved) override;

  std::vector<RequestResolved_t*> Vector_Request_Resolved_t;

};

#endif  // GOLDSORTASSEMBLER_HPP
