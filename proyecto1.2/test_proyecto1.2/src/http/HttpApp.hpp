// Copyright 2021 Jeisson Hidalgo-Cespedes. Universidad de Costa Rica. CC BY 4.0

#ifndef HTTPAPP_H
#define HTTPAPP_H

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

  /// ID de la aplicación (/fact o /gold)

 protected:
  std::string id;
  /// Cola de paquetes
  Queue<RequestResponseStruct>* requestResponseQueue;

 public:
  /// Constructor
  HttpApp() = default;
  /// Destructor
  ~HttpApp() = default;
  /// Called by the web server when the web server is started
  virtual void start();
  /// Handle HTTP requests. @see HttpServer::handleHttpRequest()
  /// @return true If this application handled the request, false otherwise
  /// and another chained application should handle it
  virtual bool handleHttpRequest(HttpRequest& httpRequest,
                                 HttpResponse& httpResponse) = 0;
  /// Called when the web server stops, in order to allow the web application
  /// clean up and finish as well
  virtual void stop();

  std::string get_ID() { return this->id; }
  Queue<RequestResponseStruct>* get_request_response_queue() {
    return this->requestResponseQueue;
  }
};

#endif  // HTTPAPP_H
