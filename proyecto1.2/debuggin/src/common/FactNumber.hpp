#ifndef FACTNUMBER_HPP
#define FACTNUMBER_HPP

#include "HttpRequest.hpp"
#include "HttpResponse.hpp"
#include <vector>

class FactNumber {
  public:
    std::vector<int64_t> numbersVector;
    HttpResponse httpResponse;
    int64_t id;
    int64_t index;
    int64_t numero;
    int64_t maxNumbers;

    FactNumber(HttpResponse response, int64_t id, int64_t index, int64_t numero,int64_t maxNumbers) 
      : httpResponse(response), id(id), index(index), numero(numero)
      , maxNumbers(maxNumbers)  {
    }

};

#endif  // FACTNUMBER_HPP