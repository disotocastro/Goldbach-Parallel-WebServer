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

  // 0. if map_vector[data.id] == null
    // 0.1 map_vector[data.id] = std::make_shared<vector<factNum>>()
    // 0.2 map_vector[data.id]->resize(data.max_num)
    // 0.3 map_vector[data.id][data.index] = data;
  // 1. else
    // 1.1 map_vector[data.id][data.index] = data;
  // checkIsComplete()

  


  // std::vector<RequestResolved_t*> Vector_Request_Resolved_t;
};

#endif  // FACTSORTASSEMBLER
