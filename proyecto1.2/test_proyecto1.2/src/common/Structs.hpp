#ifndef STRUCTS_HPP
#define STRUCTS_HPP

#include "HttpRequest.hpp"
#include "HttpResponse.hpp"

typedef struct reqRes {
    HttpRequest *httpRequest;
    HttpResponse *httpResponse;

public:
  reqRes(HttpRequest *request = nullptr, HttpResponse *response = nullptr)
    : httpRequest(request), httpResponse(response) {}

  inline bool operator==(const reqRes &other) const {
    return this->httpRequest == other.httpRequest
    && this->httpResponse == other.httpResponse;
  }
} reqRes_t;

#endif // STRUCTS_HPP
 