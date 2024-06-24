// Copyright 2024 Diego Soto, Migueledo Nuñez, William Morales
// Universidad de Costa Rica. CC BY 4.0

#include "GoldUriAnalizer.hpp"

#include <string>
#include <vector>

int GoldUriAnalizer::run() {
  this->consumeForever();

  for (int64_t i = 0; i < this->maxSolvers; i++) {
    Numbers_t temp = Numbers_t();
    produce(&temp);
  }

  return EXIT_SUCCESS;
}

void GoldUriAnalizer::consume(RequestResponseStruct_t data) {
  // If the home page was asked

  if (data.httpRequest.getMethod() == "GET" &&
      data.httpRequest.getURI() == "/") {
    this->sendErrorResponse(data.httpResponse);
  } else if (data.httpRequest.getMethod() == "GET" &&
             data.httpRequest.getURI() == "/gold") {
    this->serveHomepage(data.httpRequest, data.httpResponse);
  } else if (data.httpRequest.getURI().rfind("/gold/gold", 0) == 0) {
    if (data.httpRequest.getURI().find("number=")) {
      GoldBach(data);
    }
  } else {
    this->sendErrorResponse(data.httpResponse);
  }
}

bool GoldUriAnalizer::serveHomepage(HttpRequest& httpRequest,
                                    HttpResponse& httpResponse) {
  (void)httpRequest;

  // Set HTTP response metadata (headers)
  httpResponse.setHeader("Server", "AttoServer v1.1");
  httpResponse.setHeader("Content-type", "text/html; charset=ascii");

  // Build the body of the response
  std::string title = "GoldBach";
  httpResponse.body() << "<!DOCTYPE html>\n"
                      << "<html lang=\"en\">\n"
                      << "  <meta charset=\"ascii\"/>\n"
                      << "  <title>" << title << "</title>\n"
                      << "  <style>body {font-family: monospace}</style>\n"
                      << "  <h1>" << title << "</h1>\n"
                      << "  <form method=\"get\" action=\"/gold/gold\">\n"
                      << "    <label for=\"number\">Number</label>\n"
                      << "    <input type=\"text\" name=\"number\" required/>\n"
                      << "    <button type=\"submit\">Factorize</button>\n"
                      << "  </form>\n"
                      << "  <hr><p><a href=\"/\">Back</a></p>\n"
                      << "</html>\n";

  // Send the response to the client (user agent)
  return httpResponse.send();
}

void GoldUriAnalizer::sendErrorResponse(HttpResponse& httpResponse) {
  // Build the body for an invalid request
  std::string title = "WebApps";
  httpResponse.body()
      << "<!DOCTYPE html>\n"
      << "<html lang=\"en\">\n"
      << "  <meta charset=\"ascii\"/>\n"
      << "  <title>" << title << "</title>\n"
      << "  <style>body {font-family: monospace} .err {color: red}</style>\n"
      << "  <h1 class=\"err\">" << title << "</h1>\n"
      << "  <p>Select a wepApp</p>\n"
      << "  <hr><p><a href=\"/fact\">Go To Fact</a></p>\n"
      << "  <hr><p><a href=\"/gold\">Go To Gold</a></p>\n"
      << "</html>\n";
  httpResponse.send();
}

void GoldUriAnalizer::GoldBach(RequestResponseStruct_t data) {
  std::vector<int64_t> numbersVector = getNumbersFromURI(data.httpRequest);
  readNumbers(numbersVector, data);
}

void GoldUriAnalizer::readNumbers(std::vector<int64_t>& inputNumbers,
                                  RequestResponseStruct_t reqRes) {
  // Lee los números de la entrada estándar y los almacena en la lista
  this->Element_ID++;
  for (size_t i = 0; i < inputNumbers.size(); i++) {
    Numbers_t* Nuevo = new Numbers_t(this->Element_ID, i, inputNumbers[i],
                                     inputNumbers.size(), reqRes.httpResponse);
    // // TODO: NEW
    produce(Nuevo);
  }
}

std::vector<int64_t> GoldUriAnalizer::getNumbersFromURI(
    HttpRequest& httpRequest) {
  std::vector<int64_t> numbersVector;

  size_t pos = httpRequest.getURI().find("number=");
  std::string str = "";

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
    int valor = std::stoll(matches[0].str());
    numbersVector.push_back(valor);
    ini = matches.suffix().first;
  }
  return numbersVector;
}

void GoldUriAnalizer::consumeForever() {
  assert(this->consumingQueue);
  while (true) {
    // Get the next data to consume, or block while queue is empty
    const RequestResponseStruct_t& data = this->consumingQueue->dequeue();
    // If data is the stop condition, stop the loop
    if (data.stopCondition == 1) {
      break;
    }
    // Process this data
    this->consume(data);
  }
}
