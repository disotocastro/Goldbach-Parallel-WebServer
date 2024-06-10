#ifndef REQUESTRESPONSESTRUCTS_HPP
#define REQUESTRESPONSESTRUCTS_HPP

#include "HttpRequest.hpp"
#include "HttpResponse.hpp"

typedef struct RequestResponseStruct {
  HttpRequest httpRequest;
  HttpResponse httpResponse;

 public:
  // Constructor con parámetros por defecto
  RequestResponseStruct(HttpRequest request = HttpRequest((Socket())),
                        HttpResponse response = HttpResponse((Socket())))
      : httpRequest(request), httpResponse(response) {}

  inline bool operator==(const RequestResponseStruct& other) const {
    return this->httpRequest == other.httpRequest &&
           this->httpResponse == other.httpResponse;
  }
} RequestResponseStruct_t;

#endif  // REQUESTRESPONSESTRUCTS_HPP