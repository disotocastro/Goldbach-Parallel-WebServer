#ifndef REQUESTRESPONSESTRUCTS_HPP
#define REQUESTRESPONSESTRUCTS_HPP

#include "HttpRequest.hpp"
#include "HttpResponse.hpp"

typedef struct RequestResponseStruct {
    HttpRequest *httpRequest;
    HttpResponse *httpResponse;
    int id; 

public:
    // Constructor con parámetros por defecto
    RequestResponseStruct(HttpRequest *request = nullptr, HttpResponse *response = nullptr, int id = 0)
        : httpRequest(request), httpResponse(response), id(id) {}

    inline bool operator==(const RequestResponseStruct &other) const {
        return this->httpRequest == other.httpRequest
            && this->httpResponse == other.httpResponse
            && this->id == other.id;
    }
} RequestResponseStruct;

#endif // REQUESTRESPONSESTRUCTS_HPP
