// Copyright 2021 Jeisson Hidalgo-Cespedes. Universidad de Costa Rica. CC BY 4.0

#include <algorithm>
#include <cassert>
#include <iostream>
#include <regex>
#include <stdexcept>
#include <string>
#include <cstring>

#include "GoldWebApp.hpp"
#include "GoldSolver.hpp"
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
    return this->serveGoldbach(httpRequest, httpResponse);
  }

  // Unrecognized request
  return false;
}

bool GoldWebApp::serveHomepage(HttpRequest& httpRequest
  , HttpResponse& httpResponse) {
  (void)httpRequest;

  // Set HTTP response metadata (headers)
  httpResponse.setHeader("Server", "AttoServer v1.1");
  httpResponse.setHeader("Content-type", "text/html; charset=ascii");

  // Build the body of the response
  std::string title = "Goldbach sums ";
  httpResponse.body() << "<!DOCTYPE html>\n"
    << "<html lang=\"en\">\n"
    << "  <meta charset=\"ascii\"/>\n"
    << "  <title>" << title << "</title>\n"
    << "  <style>body {font-family: monospace}</style>\n"
    << "  <h1>" << title << "</h1>\n"
    << "  <form method=\"get\" action=\"/gold/gold\">\n"
    << "    <label for=\"number\">Number</label>\n"
    << "    <input type=\"arrays\" name=\"number\" required/>\n"
    << "    <button type=\"submit\">Get sums</button>\n"
    << "  </form>\n"
    << "</html>\n";

  // Send the response to the client (user agent)
  return httpResponse.send();
}

bool GoldWebApp::serveGoldbach(HttpRequest& httpRequest,
                               HttpResponse& httpResponse) {
  (void)httpRequest;
  std::string str = "";
  int longitud = 0;
  bool hayError = false;

  // Set HTTP response metadata (headers)
  httpResponse.setHeader("Server", "AttoServer v1.0");
  httpResponse.setHeader("Content-type", "text/html; charset=ascii");

  std::vector<int64_t> numbersVector;
  // Obtener los números del URI
  if (!getNumbersFromURI(httpRequest, numbersVector, longitud, str)) {
    hayError = true;
  }

  if (!hayError) {
    sendSuccessResponse(numbersVector, httpResponse);
  } else {
    sendErrorResponse(httpResponse);
  }
  return httpResponse.send();
}

bool GoldWebApp::getNumbersFromURI(HttpRequest& httpRequest,
                                   std::vector<int64_t>& numbersVector,
                                   int longitud, std::string str) {
  if (size_t pos = httpRequest.getURI().find("number=")) {
    std::string numbersString = httpRequest.getURI().substr(pos + 7);
    // Uniformar el URI para que el separador sea espacio
    std::regex coma("%..");  // símbolo porcentaje y dos caracteres cualquiera
    std::string nuevoUri = std::regex_replace(numbersString, coma, " ");
    // Expresión regular para buscar números enteros
    std::regex patron("-?[0-9]+");
    std::smatch matches;
    std::string::const_iterator ini = nuevoUri.begin();
    std::string::const_iterator fin = nuevoUri.end();
    // Buscar números en el URI modificado
    while (std::regex_search(ini, fin, matches, patron)) {
      str = matches.str();
      longitud = str.size();
      if (longitud > 19) {
        return false;   // Hay un error, número demasiado grande
      }
      int valor = std::stoll(matches[0].str());
      numbersVector.push_back(valor);
      ini = matches.suffix().first;
    }
    return true;
  } else {
    return false;   // Hay un error, no se encontró la cadena "number="
  }
}

void GoldWebApp::sendSuccessResponse(const std::vector<int64_t>& numbersVector,
                                     HttpResponse& httpResponse) {
  std::string title = " Goldbach Sums";
  httpResponse.body() << "<!DOCTYPE html>\n"
                      << "<html lang=\"en\">\n"
                      << "  <meta charset=\"ascii\"/>\n"
                      << "  <title>" << title << "</title>\n"
                      << "  <style>\n"
                      << "    body {font-family: monospace}\n"
                      << "    .blue {color: blue}\n"
                      << "    .small {font-size: 0.8em; color: black}\n"
                      << "  </style>\n"
                      << "  <h1>" << title << "</h1>\n";
  std::vector<int64_t> numbersTemp = numbersVector;
  GoldSolver goldbach = GoldSolver(numbersTemp);

  for (size_t i = 0; i < numbersVector.size(); i++) {
    std::string resultado =  goldbach.stringSums[i];
    httpResponse.body() << " <h1>" << resultado << "</h1>\n";
  }
  httpResponse.body() << "</html>\n";
}

void GoldWebApp::sendErrorResponse(HttpResponse& httpResponse) {
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
