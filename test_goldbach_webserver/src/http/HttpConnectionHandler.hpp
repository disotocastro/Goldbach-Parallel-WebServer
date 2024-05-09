// TODO: Metodo CONSUME, consume(&socket)

#ifndef HTTPCONNECTIONHANDLER_HPP
#define HTTPCONNECTIONHANDLER_HPP

#include "HttpApp.hpp"
#include "Consumer.hpp"
#include "Socket.hpp"

class HttpConnectionHandler : public Consumer <Socket> {
 public:

  int run() override;
  void consume(Socket client) override;

  /// Route, that provide an answer according to the URI value
  /// For example, home page is handled different than a number
  bool route(HttpRequest& httpRequest, HttpResponse& httpResponse);

  /// Sends a page for a non found resouce in this server. This method is called
  /// if none of the registered web applications handled the request.
  /// If you want to override this method, create a web app, e.g NotFoundWebApp
  /// that reacts to all URIs, and chain it as the last web app
  bool serveNotFound(HttpRequest& httpRequest, HttpResponse& httpResponse);


  /// Called each time an HTTP request is received. Web server should analyze
  /// the request object and assemble a response with the response object.
  /// Finally send the response calling the httpResponse.send() method.
  /// @return true on success and the server will continue handling further
  /// HTTP requests, or false if server should stop accepting requests from
  /// this client (e.g: HTTP/1.0)
  virtual bool handleHttpRequest(HttpRequest& httpRequest, 
                                 HttpResponse& httpResponse);

  


 
 protected:
 
};




#endif  // HTTPCONNECTIONHANDLER_HPP



