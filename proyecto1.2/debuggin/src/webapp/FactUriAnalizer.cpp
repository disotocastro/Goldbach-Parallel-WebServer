// Copyright 2024 Diego Soto, Migueledo Nuñez, William Moraes
// Universidad de Costa Rica. CC BY 4.0
#include "FactUriAnalizer.hpp"

#include <string>
#include <vector>

#include "HttpApp.hpp"
#include "HttpRequest.hpp"
#include "HttpResponse.hpp"
#include "Log.hpp"
#include "NetworkAddress.hpp"
#include "HttpDispatcher.hpp"

int FactUriAnalizer::run() {
  this->consumeForever();
  return EXIT_SUCCESS;
}

void FactUriAnalizer::consume(RequestResponseStruct_t data) {
  // If the home page was asked
  if (data.httpRequest.getMethod() == "GET" &&
      data.httpRequest.getURI() == "/fact") {
    this->serveHomepage(data.httpRequest, data.httpResponse);
  }

  // if (data.httpRequest.getURI().rfind("/fact/fact", 0) == 0) {
    // return this->serveFactorization(data.httpRequest, data.httpResponse);

    /**
    Aqui no se hace un serve factorization, aqui se tienen que extraer
    los numeros del uri
     */
  // }
}

bool FactUriAnalizer::serveHomepage(HttpRequest& httpRequest,
                                    HttpResponse& httpResponse) {
  (void)httpRequest;

  // Set HTTP response metadata (headers)
  httpResponse.setHeader("Server", "AttoServer v1.1");
  httpResponse.setHeader("Content-type", "text/html; charset=ascii");

  // Build the body of the response
  std::string title = "Prime factorization";
  httpResponse.body()
      << "<!DOCTYPE html>\n"
      << "<html lang=\"en\">\n"
      << "  <meta charset=\"ascii\"/>\n"
      << "  <title>" << title << "</title>\n"
      << "  <style>body {font-family: monospace}</style>\n"
      << "  <h1>" << title << "</h1>\n"
      << "  <form method=\"get\" action=\"/fact/fact\">\n"
      << "    <label for=\"number\">Number</label>\n"
      << "    <input type=\"arrays\" name=\"number\" required/>\n"
      << "    <button type=\"submit\">Factorize</button>\n"
      << "  </form>\n"
      << "</html>\n";

  // Send the response to the client (user agent)
  return httpResponse.send();
}


