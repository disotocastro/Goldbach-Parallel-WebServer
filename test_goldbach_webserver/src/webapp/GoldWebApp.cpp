// Copyright 2021 Jeisson Hidalgo-Cespedes. Universidad de Costa Rica. CC BY 4.0

#include <algorithm>
#include <cassert>
#include <iostream>
#include <regex>
#include <stdexcept>
#include <string>

#include "GoldWebApp.hpp"
#include "HttpRequest.hpp"
#include "HttpResponse.hpp"

GoldWebApp::GoldWebApp() {
}

GoldWebApp::~GoldWebApp() {
}

void GoldWebApp::start() {
  // TODO(you): Start producers, consumers, assemblers...
}

void GoldWebApp::stop() {
  // TODO(you): Stop producers, consumers, assemblers...
}

bool GoldWebApp::handleHttpRequest(HttpRequest& httpRequest,
    HttpResponse& httpResponse) {
  // If the home page was asked
  if (httpRequest.getMethod() == "GET" && httpRequest.getURI() == "/gold") {
    return this->serveHomepage(httpRequest, httpResponse);
  }

  // If the request starts with "gold/" is for this web app
  if (httpRequest.getURI().rfind("/gold/gold", 0) == 0) {
    return this->serveFactorization(httpRequest, httpResponse);
  }

  // Unrecognized request
  return false;
}

// TODO: Fix code redundancy in the following methods
bool GoldWebApp::serveHomepage(HttpRequest& httpRequest
  , HttpResponse& httpResponse) {
  (void)httpRequest;

  // Set HTTP response metadata (headers)
  httpResponse.setHeader("Server", "AttoServer v1.1");
  httpResponse.setHeader("Content-type", "text/html; charset=ascii");

  // Build the body of the response
  std::string title = "Prime factorization";
  httpResponse.body() << "<!DOCTYPE html>\n"
    << "<html lang=\"en\">\n"
    << "  <meta charset=\"ascii\"/>\n"
    << "  <title>" << title << "</title>\n"
    << "  <style>body {font-family: monospace}</style>\n"
    << "  <h1>" << title << "</h1>\n"
    << "  <form method=\"get\" action=\"/fact\">\n"
    << "    <label for=\"number\">Number</label>\n"
    // TODO: Estos valores number, tienen que ser strings, ya que number
    // solo admite un valor, luego cambiar la expresion regular de abajo
    << "    <input type=\"number\" name=\"number\" required/>\n"
    << "    <button type=\"submit\">Get sums</button>\n"
    << "  </form>\n"
    << "</html>\n";

  // Send the response to the client (user agent)
  return httpResponse.send();
}

bool GoldWebApp::serveFactorization(HttpRequest& httpRequest
  , HttpResponse& httpResponse) {
  (void)httpRequest;

  // Set HTTP response metadata (headers)
  httpResponse.setHeader("Server", "AttoServer v1.0");
  httpResponse.setHeader("Content-type", "text/html; charset=ascii");

  // If a number was asked in the form "/fact/1223"
  // or "/fact?number=1223"
  // TODO(you): URI can be a multi-value list, e.g: 100,2784,-53,200771728
  // TODO(you): Use arbitrary precision for numbers larger than int64_t
  // TODO(you): Modularize this method
  std::smatch matches;
  // TODO: Cambiar esta expresion regular
  std::regex inQuery("^/fact(/|\\?number=)(\\d+)$");
  if (std::regex_search(httpRequest.getURI(), matches, inQuery)) {
    assert(matches.length() >= 3);
    const int64_t number = std::stoll(matches[2]);

    // TODO(you): Factorization must not be done by factorization threads
    // Build the body of the response
    std::string title = "Prime factorization of " + std::to_string(number);
    httpResponse.body() << "<!DOCTYPE html>\n"
      << "<html lang=\"en\">\n"
      << "  <meta charset=\"ascii\"/>\n"
      << "  <title>" << title << "</title>\n"
      << "  <style>body {font-family: monospace} .err {color: red}</style>\n"
      << "  <h1>" << title << "</h1>\n"
      << "  <h2>200</h2>\n"
      << "  <p>200 = 2<sup>3</sup> 5<sup>2</sup></p>\n"
      << "  <h2 class=\"err\">-3</h2>\n"
      << "  <p>-3: invalid number</p>\n"
      << "  <h2>13</h2>\n"
      << "  <p>-13 is prime</p>\n"
      << "  <hr><p><a href=\"/\">Back</a></p>\n"
      << "</html>\n";
  } else {
    // Build the body for an invalid request
    std::string title = "Invalid request";
    httpResponse.body() << "<!DOCTYPE html>\n"
      << "<html lang=\"en\">\n"
      << "  <meta charset=\"ascii\"/>\n"
      << "  <title>" << title << "</title>\n"
      << "  <style>body {font-family: monospace} .err {color: red}</style>\n"
      << "  <h1 class=\"err\">" << title << "</h1>\n"
      << "  <p>Invalid request for factorization</p>\n"
      << "  <hr><p><a href=\"/\">Back</a></p>\n"
      << "</html>\n";
  }

  // Send the response to the client (user agent)
  return httpResponse.send();
}
