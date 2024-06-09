#include "GoldSolverAssambler.hpp"
#include "GoldSortAssembler.hpp"
#include "numbers.hpp"


Sort_Assembler::Sort_Assembler(
    Queue<Numbers_t*>* numbers_t_queue_resolved,
    Queue<RequestResolved_t*>* request_resolved_queue) {
  this->setConsumingQueue(numbers_t_queue_resolved);
  this->setProducingQueue(request_resolved_queue);

  Vector_Request_Resolved_t = std::vector<RequestResolved_t*>();
}

int Sort_Assembler::run() {
  this->consumeForever();
  return EXIT_SUCCESS;
}

void Sort_Assembler::consume(Numbers_t* numbers_t_resolved) {
  int64_t ID = numbers_t_resolved->id;
  int64_t maxNumbers = numbers_t_resolved->maxNumbers;
  bool exist = false;
  int64_t arrayPosition = numbers_t_resolved->index;

  for (size_t i = 0; i < Vector_Request_Resolved_t.size(); i++) {
    if (ID == Vector_Request_Resolved_t[i]->id) {
      Vector_Request_Resolved_t[i]->GoldbachSumsArray[arrayPosition] = numbers_t_resolved;
      Vector_Request_Resolved_t[i]->counterNumbers ++;
      
      if (maxNumbers == Vector_Request_Resolved_t[i]->maxNumbers) {
        produce(Vector_Request_Resolved_t[i]);
      }

      exist = true;
      break;
    }
  }
  
  if (exist == false) {
    RequestResolved_t* temp = new RequestResolved_t(ID, maxNumbers);
    Vector_Request_Resolved_t.push_back(temp);
    int64_t size = Vector_Request_Resolved_t.size() - 1;
    Vector_Request_Resolved_t[size]->GoldbachSumsArray[arrayPosition] = numbers_t_resolved;
    Vector_Request_Resolved_t[size]->counterNumbers ++;
    
    if (maxNumbers == Vector_Request_Resolved_t[size]->maxNumbers) {
        produce(Vector_Request_Resolved_t[size]);
    }
  }
}

/*
  1. Leer el ID de numbers_t que se lee
  2. Si no hay un request_solved para ese ID se crea uno en el vector
  3. Si ya existe se insera en el que le corresponde, en el index que le
  corresponde
  4. Cuando  mete un elemento nuevo, aumeenta en 1 la cantidad de elementos
  exististen, y si la cantidad de elementos existentes es igual a la
  cantidad_maxima, saca del vector la estructura y la produce.
*/