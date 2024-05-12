// Copyright 2021 Jeisson Hidalgo-Cespedes. Universidad de Costa Rica. CC BY 4.0

#include <algorithm>
#include <cassert>
#include <iostream>
#include <regex>
#include <stdexcept>
#include <string>

#include "FactWebApp.hpp"
#include "FactSolver.hpp"
#include "HttpRequest.hpp"
#include "HttpResponse.hpp"

FactWebApp::FactWebApp() {
}

FactWebApp::~FactWebApp() {
}

void FactWebApp::start() {
  // TODO(you): Start producers, consumers, assemblers...
}

void FactWebApp::stop() {
  // TODO(you): Stop producers, consumers, assemblers...
}

bool FactWebApp::handleHttpRequest(HttpRequest& httpRequest,
    HttpResponse& httpResponse) {
  // If the home page was asked
  if (httpRequest.getMethod() == "GET" && httpRequest.getURI() == "/fact") {
    return this->serveHomepage(httpRequest, httpResponse);
  }

  // If the request starts with "fact/" is for this web app
  if (httpRequest.getURI().rfind("/fact/fact", 0) == 0) {
    return this->serveFactorization(httpRequest, httpResponse);
  }

  // Unrecognized request
  return false;
}

// TODO(you): Fix code redundancy in the following methods

bool FactWebApp::serveHomepage(HttpRequest& httpRequest
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
    << "  <form method=\"get\" action=\"/fact/fact\">\n"
    << "    <label for=\"number\">Number</label>\n"
    << "    <input type=\"arrays\" name=\"number\" required/>\n"
    << "    <button type=\"submit\">Factorize</button>\n"
    << "  </form>\n"
    << "</html>\n";

  // Send the response to the client (user agent)
  return httpResponse.send();
}

bool FactWebApp::serveFactorization(HttpRequest& httpRequest
  , HttpResponse& httpResponse) {
  (void)httpRequest;

  // Set HTTP response metadata (headers)
  httpResponse.setHeader("Server", "AttoServer v1.0");
  httpResponse.setHeader("Content-type", "text/html; charset=ascii");

  // Se exctrae del URI los numeros y se almacenan en un vector
  if (size_t pos = httpRequest.getURI().find("number=")) {
   if (pos == std::string::npos) {
        std::cerr << "No se encontraron números en la URL." << std::endl;
        return 1;
    }
    // El 7 es la longitud de "number="
    std::string numbersString = httpRequest.getURI().substr(pos + 7); 
    // Vector de numeros enteros con los numeros del URI
    std::vector<int64_t> numbersVector = fillVector(numbersString);
    // Vector de Strings con el resultado de cada facto
    std::vector<std::string> results = getResults(numbersVector);

    std::string title = "Prime factorization";
    httpResponse.body() << "<!DOCTYPE html>\n"
      << "<html lang=\"en\">\n"
      << "  <meta charset=\"ascii\"/>\n"
      << "  <title>" << title << "</title>\n"
      << "  <style>\n"
      << "    body {font-family: monospace}\n"
      << "    .blue {color: blue}\n"
      << "    .small {font-size: 0.8em; color: black}\n"
      << "  </style>\n"
      << "  <h1>" << title << "</h1>\n" ;

      for (size_t i = 0; i < numbersVector.size(); i++) {
        std::string numero = std::to_string(numbersVector[i]);
        std::string resultado = results[i];
        httpResponse.body()
          << "  <h2 class=\"blue\">" << numero 
          << ": <span class=\"small\">" << resultado << "</span></h2>\n";
      }
      httpResponse.body()
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

std::vector<int64_t> FactWebApp::fillVector(std::string numbersString) {
  std::vector<int64_t> numbersVector;
  // Elimina los caracteres especiales '%2C' que representan comas
  while (true) {
      size_t commaPos = numbersString.find("%2C");
      if (commaPos == std::string::npos) break;
      numbersString.replace(commaPos, 3, " ");
  }

  // Ahora leemos los números uno por uno desde el stringstream
  std::istringstream iss(numbersString);
  int number;
  while (iss >> number) {
      numbersVector.push_back(number);
  }

  return numbersVector;
}

std::vector<std::string> FactWebApp::getResults(
                                           std::vector<int64_t> numbersVector) {
  FactSolver Factorizacion;
  std::vector<std::string> results = Factorizacion.FactorizeVector(numbersVector);

  return results;
}
