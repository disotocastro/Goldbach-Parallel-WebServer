// Copyright 2024 Diego Soto, Migueledo Nuñez, William MoraeLs
// Universidad de Costa Rica. CC BY 4.0

#ifndef FACTSORTASSEMBLER
#define FACTSORTASSEMBLER

#include <vector>


#include "Assembler.hpp"
#include "FactNumber.hpp"
#include "HttpApp.hpp"
#include "Queue.hpp"

class FactSortAssembler
    : public Assembler<FactNumber*, std::vector<FactNumber*>> {
 public:
  int run() override;
  void consume(FactNumber* data) override;


  std::map<int64_t, std::vector<FactNumber*>> map_vector;
  std::map<int64_t, int> map_counter;



  // std::vector<RequestResolved_t*> Vector_Request_Resolved_t;
};

#endif  // FACTSORTASSEMBLER
