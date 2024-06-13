// Copyright 2021 Jeisson Hidalgo-Cespedes. Universidad de Costa Rica. CC BY 4.0

#ifndef HTTPAPP_H
#define HTTPAPP_H

#include <string>

#include "Queue.hpp"
#include "RequestResponseStruct.hpp"
#include "common.hpp"

class HttpRequest;
class HttpResponse;

/**
@brief Base class for all web applications that can be registered with the
web server.
*/
class HttpApp {
  /// Web application objects are usually complex. This base class does not
  /// require child classes to allow copying
  DISABLE_COPY(HttpApp);

 public:
  /// Key que identifica cual webApp es
  std::string key;
  /// Cola de consumo para dicha webApp
  Queue<RequestResponseStruct_t>* entranceQueue;
  /// Constructor
  HttpApp() = default;
  /// Destructor
  ~HttpApp() = default;
  /// Called by the web server when the web server is started
  virtual void start();
  /// Handle HTTP requests. @see HttpServer::handleHttpRequest()
  /// @return true If this application handled the request, false otherwise
  /// and another chained application should handle it

  // virtual bool handleHttpRequest(HttpRequest& httpRequest,
  //   HttpResponse& httpResponse) = 0;
  /// Called when the web server stops, in order to allow the web application
  /// clean up and finish as well
  virtual void stop();
};

#endif  // HTTPAPP_H
