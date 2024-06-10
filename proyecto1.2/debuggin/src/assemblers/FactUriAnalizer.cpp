// Copyright 2024 Diego Soto, Migueledo Nuñez, William Morales
// Universidad de Costa Rica. CC BY 4.0
#include "FactUriAnalizer.hpp"

#include <string>
#include <vector>

#include "FactNumber.hpp"
#include "HttpApp.hpp"
#include "HttpDispatcher.hpp"
#include "HttpRequest.hpp"
#include "HttpResponse.hpp"
#include "Log.hpp"
#include "NetworkAddress.hpp"

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

  if (data.httpRequest.getURI().rfind("/fact/fact", 0) == 0) {
    if (size_t pos = data.httpRequest.getURI().find("number=")) {
      factUri(data.httpRequest, data.httpResponse);

      if (pos == std::string::npos) {
        std::cerr << "No se encontraron números en la URL." << std::endl;
      }
      // El 7 es la longitud de "number="
      std::string numbersString = data.httpRequest.getURI().substr(pos + 7);

      std::vector<int64_t> numbersVector = fillVector(numbersString);
      Element_ID++;
      for (size_t i = 0; i < numbersVector.size(); i++) {
        FactNumber* number =
            new FactNumber(data.httpResponse, this->Element_ID, i,
                           numbersVector[i], numbersVector.size());
        produce(number);
      }
    }
  }
}

void FactUriAnalizer::factUri(HttpRequest& httpRequest,
                              HttpResponse& httpResponse) {}

bool FactUriAnalizer::serveHomepage(HttpRequest& httpRequest,
                                    HttpResponse& httpResponse) {
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
                      << "    <input type=\"text\" name=\"number\" required/>\n"
                      << "    <button type=\"submit\">Factorize</button>\n"
                      << "  </form>\n"
                      << "</html>\n";

  // Send the response to the client (user agent)
  return httpResponse.send();
}

std::vector<int64_t> FactUriAnalizer::fillVector(std::string numbersString) {
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
