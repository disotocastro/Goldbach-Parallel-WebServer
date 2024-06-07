#ifndef STRUCTS_HPP
#define STRUCTS_HPP

#include "HttpRequest.hpp"
#include "HttpResponse.hpp"

typedef struct RequestResponseStruct {
    HttpRequest *httpRequest;
    HttpResponse *httpResponse;

public:
  RequestResponseStruct(HttpRequest *request = nullptr, HttpResponse *response = nullptr)
    : httpRequest(request), httpResponse(response) {}

  inline bool operator==(const RequestResponseStruct &other) const {
    return this->httpRequest == other.httpRequest
    && this->httpResponse == other.httpResponse;
  }
} RequestResponseStruct;

#endif // STRUCTS_HPP
 