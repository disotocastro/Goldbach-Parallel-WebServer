// Copyright 2021 Jeisson Hidalgo-Cespedes. Universidad de Costa Rica. CC BY 4.0

#ifndef GOLDWEBAPP_HPP
#define GOLDWEBAPP_HPP

#include "HttpApp.hpp"

/**
@brief A web application that calculates prime factors
*/
class GoldWebApp : public HttpApp {
  /// Objects of this class cannot be copied
  DISABLE_COPY(GoldWebApp);

 public:
  /// Constructor
  GoldWebApp();
  /// Destructor
  ~GoldWebApp();
  /// Called by the web server when the web server is started
  void start() override;
  /// Handle HTTP requests. @see HttpServer::handleHttpRequest()
  /// @return true If this application handled the request, false otherwise
  /// and another chained application should handle it
  bool handleHttpRequest(HttpRequest& httpRequest,
    HttpResponse& httpResponse) override;
  /// Called when the web server stops, in order to allow the web application
  /// clean up and finish as well
  void stop() override;

 protected:
  /// Handle HTTP requests. @see HttpServer::handleHttpRequest()
  /// @return true If this application handled the request, false otherwise
  /// Sends the homepage as HTTP response
  bool serveHomepage(HttpRequest& httpRequest, HttpResponse& httpResponse);
  /// Handle a HTTP request that starts with "/fact"
  /// @return true if the factorization was handled, false if it must be
  /// handled by another application
  bool serveFactorization(HttpRequest& httpRequest, HttpResponse& httpResponse);
};

#endif  // GOLDWEBAPP_HPP
