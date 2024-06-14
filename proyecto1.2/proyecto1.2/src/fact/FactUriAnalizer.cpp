// Copyright 2024 Diego Soto, Migueledo Nuñez, William Morales
// Universidad de Costa Rica. CC BY 4.0

#include "FactUriAnalizer.hpp"

#include "FactNumber.hpp"

int FactUriAnalizer::run() {
  this->consumeForever();

  for (int64_t i = 0; i < this->maxSolvers; i++) {
    FactNumber temp = FactNumber();
    produce(&temp);
  }

  return EXIT_SUCCESS;
}

void FactUriAnalizer::consume(RequestResponseStruct_t data) {
  // If the home page was asked

  if (data.httpRequest.getMethod() == "GET" &&
      data.httpRequest.getURI() == "/") {
    this->sendErrorResponse(data.httpResponse);
  } else if (data.httpRequest.getMethod() == "GET" &&
             data.httpRequest.getURI() == "/fact") {
    this->serveHomepage(data.httpRequest, data.httpResponse);
  } else if (data.httpRequest.getURI().rfind("/fact/fact", 0) == 0) {
    if (size_t pos = data.httpRequest.getURI().find("number=")) {
      factUri(data, pos);
    }
  } else {
    this->sendErrorResponse(data.httpResponse);
  }
}

void FactUriAnalizer::consumeForever() {
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

void FactUriAnalizer::factUri(RequestResponseStruct_t data, size_t pos) {
  // El 7 es la longitud de "number="
  std::string numbersString = data.httpRequest.getURI().substr(pos + 7);

  std::vector<int64_t> numbersVector = fillVector(numbersString);

  // sino hay numeros en el uri
  if (numbersVector.size() == 0) {
    this->sendErrorResponse(data.httpResponse);
  }

  Element_ID++;

  for (size_t i = 0; i < numbersVector.size(); i++) {
    FactNumber* number = new FactNumber(data.httpResponse, this->Element_ID, i,
                                        numbersVector[i], numbersVector.size());
    produce(number);
  }
}

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
                      << "  <hr><p><a href=\"/\">Back</a></p>\n"
                      << "</html>\n";

  // Send the response to the client (user agent)
  return httpResponse.send();
}

void FactUriAnalizer::sendErrorResponse(HttpResponse& httpResponse) {
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
  int64_t number;
  while (iss >> number) {
    numbersVector.push_back(number);
  }

  return numbersVector;
}
