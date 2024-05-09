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
  bool route(HttpRequest& httpRequest, HttpResponse& httpResponse);

  


 
 protected:
 
};




#endif  // HTTPCONNECTIONHANDLER_HPP



