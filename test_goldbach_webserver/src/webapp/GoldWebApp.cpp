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
  std::string title = "Goldbach sums";
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

  std::string uri = httpRequest.getURI();
  
  // Eliminar "http://localhost:8080/fact/fact?number="
  size_t pos = uri.find("number=");
  if (pos != std::string::npos) {
    uri = uri.substr(pos + 7); 
    // Uniformar el URI para que el separador sea espacio
    std::regex coma("%..");  // símbolo porcentaje y dos caracteres cualquiera
    std::string nuevoUri = std::regex_replace(uri, coma, " ");
    // Expresión regular para buscar números enteros
    std::regex patron("-?[0-9]+");
    std::smatch matches;
    std::string::const_iterator ini = nuevoUri.begin();
    std::string::const_iterator fin = nuevoUri.end();

    std::vector<int> numbersVector; // Vector para almacenar todos los números
    
    // Buscar números en el URI modificado
    while (std::regex_search(ini, fin, matches, patron)) {
      int valor = std::stoi(matches[0].str());
      numbersVector.push_back(valor);
      ini = matches.suffix().first;
    }
  
    // TODO(you): Factorization must not be done by factorization threads
    // Build the body of the response
    std::string title = "Goldbach Sums ";
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
      << "  <p>Invalid request for Goldbach sums</p>\n"
      << "  <hr><p><a href=\"/\">Back</a></p>\n"
      << "</html>\n";
  }

  // Send the response to the client (user agent)
  return httpResponse.send();
}
