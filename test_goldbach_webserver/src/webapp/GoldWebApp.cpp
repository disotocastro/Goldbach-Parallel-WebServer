// Copyright 2021 Jeisson Hidalgo-Cespedes. Universidad de Costa Rica. CC BY 4.0

#include <algorithm>
#include <cassert>
#include <iostream>
#include <regex>
#include <vector>
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

bool GoldWebApp::serveGoldbach(HttpRequest& httpRequest, HttpResponse& httpResponse) {
  (void)httpRequest;
  std::vector<int64_t> numbersVector;
  bool hayError = false;
  // Parse the HTTP request and extract numbers
  numbersVector = parseHttpRequest(httpRequest, hayError);
  // If there was an error parsing the request, return an error response
  if (hayError) {
    return sendErrorResponse(httpResponse);
  }
  // Build and send the successful response with Goldbach sums
  return sendSuccessResponse(numbersVector, httpResponse);
}

std::vector<int64_t> GoldWebApp::parseHttpRequest(HttpRequest& httpRequest, bool& hayError) {
  std::vector<int64_t> numbersVector;
  std::string numbersString = "";
  size_t pos = httpRequest.getURI().find("number=");
  // If "number=" was found in the URI, extract the numbers string
  if (pos != std::string::npos) {
    numbersString = httpRequest.getURI().substr(pos + 7);
    // Convert the string of numbers into a vector of integers
    std::regex numberRegex("-?[0-9]+");
    std::smatch matches;
    std::string::const_iterator ini = numbersString.begin();
    std::string::const_iterator fin = numbersString.end();
    // Extract numbers from the string using regular expressions
    while (std::regex_search(ini, fin, matches, numberRegex)) {
      std::string numberStr = matches.str();
      int64_t number = std::stoll(numberStr);
      // Check if the number exceeds the maximum allowed size
      if (numberStr.size() > 19) {
          hayError = true;
          return numbersVector;
      }
      numbersVector.push_back(number);
      ini = matches.suffix().first;
    }
  }

  if (numbersVector.empty()) {
    hayError = true;
  }
  return numbersVector;
}

std::vector<int64_t> GoldWebApp::extractNumbers(const std::string& numbersString, bool& hayError) {
  std::vector<int64_t> numbersVector;
  std::regex numberRegex("-?[0-9]+");
  std::smatch matches;
  std::string::const_iterator ini = numbersString.begin();
  std::string::const_iterator fin = numbersString.end();
  // Extract numbers from the string using regular expressions
  while (std::regex_search(ini, fin, matches, numberRegex)) {
    std::string numberStr = matches.str();
    int64_t number = std::stoll(numberStr);
    // Check if the number exceeds the maximum allowed size
    if (numberStr.size() > 19) {
      hayError = true;
      return numbersVector;
    }
    numbersVector.push_back(number);
    ini = matches.suffix().first;
  }
  return numbersVector;
}

bool GoldWebApp::sendSuccessResponse(const std::vector<int64_t>& numbersVector, HttpResponse& httpResponse) {
  httpResponse.setHeader("Server", "AttoServer v1.0");
  httpResponse.setHeader("Content-type", "text/html; charset=ascii");

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
  // Create a copy of numbersVector
  std::vector<int64_t> numbersTemp = numbersVector;
  // Calculate Goldbach sums and add them to the HTML response
  GoldSolver goldbach = GoldSolver(numbersTemp);
  for (size_t i = 0; i < numbersTemp.size(); i++) {
    std::string resultado = goldbach.stringSums[i];
    httpResponse.body() << " <h1>" << resultado << "</h1>\n";
  }
  httpResponse.body() << "</html>\n";
  return httpResponse.send();
}

bool GoldWebApp::sendErrorResponse(HttpResponse& httpResponse) {
  httpResponse.setHeader("Server", "AttoServer v1.0");
  httpResponse.setHeader("Content-type", "text/html; charset=ascii");
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
  return httpResponse.send();
}
