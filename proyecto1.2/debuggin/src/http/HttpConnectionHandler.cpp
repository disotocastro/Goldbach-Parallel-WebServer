// Copyright 2024 Diego Soto, Migueledo Nuñez, William Morales
// Universidad de Costa Rica. CC BY 4.0
#include "HttpConnectionHandler.hpp"

#include <string>
#include <vector>

#include "HttpApp.hpp"
#include "HttpRequest.hpp"
#include "HttpResponse.hpp"
#include "Log.hpp"
#include "NetworkAddress.hpp"


int HttpConnectionHandler::run() {
  this->consumeForever();
  return EXIT_SUCCESS;
}

HttpConnectionHandler::HttpConnectionHandler(){}

void HttpConnectionHandler::consume(Socket data) {
  /// While the same client asks for HTTP requests in the same connection
  while (true) {
    /// Create an object that parses the HTTP request from the socket
    HttpRequest httpRequest(data);

    /// If the request is not valid or an error happened
    if (!httpRequest.parse()) {
      /// Non-valid requests are normal after a previous valid request. Do not
      /// close the connection yet, because the valid request may take time to
      /// be processed. Just stop waiting for more requests
      break;
    }

    /// A complete HTTP client request was received. Create an object for the
    /// server responds to that client's request
    HttpResponse httpResponse(data);

    RequestResponseStruct_t reqRes(httpRequest, httpResponse);
    
    /// If subclass did not handle the request or the client used HTTP/1.0
    if (httpRequest.getHttpVersion() == "HTTP/1.0") {
      /// The socket will not be more used, close the connection
      data.close();
      break;
    }

    
    produce(reqRes);

  }
}

