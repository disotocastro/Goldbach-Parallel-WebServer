// Copyright 2021 Jeisson Hidalgo-Cespedes. Universidad de Costa Rica. CC BY 4.0

#include "GoldWebApp.hpp"

#include <algorithm>
#include <cassert>
#include <cstring>
#include <iostream>
#include <stdexcept>
#include <string>

#include "GoldSolver.hpp"
#include "HttpApp.hpp"
#include "HttpRequest.hpp"
#include "HttpResponse.hpp"
#include "Queue.hpp"
#include "RequestResponseStruct.hpp"
#include "numbers.hpp"

// TODO: Incilizar vector de Gold Solvers
//  void HttpServer::createThreads() {
//    for (int64_t i = 0; i < this->handlers; i++) {
//      // CREA UN HANDLER
//      this->vectorHandlers[i] = new
//      HttpConnectionHandler(&this->applications);
//      this->vectorHandlers[i]->setConsumingQueue(this->socketsQueue);
//      this->vectorHandlers[i]->setProducingQueue(this->requestResponseQueue);
//      this->vectorHandlers[i]->startThread();
//    }
//  }

GoldWebApp::GoldWebApp() {}

GoldWebApp::~GoldWebApp() {}

void GoldWebApp::start() {
  // Se incializan las colas
  this->id = "/gold";
  this->requestResponseQueue = new Queue<RequestResponseStruct>;
  this->numbersQueue = new Queue<Numbers_t*>;
  this->uriAnalyzer = new URI_Analyzer(requestResponseQueue, numbersQueue);
  this->uriAnalyzer->startThread();
  this->numbers_t_queue_resolved = new Queue<Numbers_t*>;

  // Vector de solvers
  int64_t n_solvers = std::thread::hardware_concurrency();
  this->vectorSolverAssemblers.resize(n_solvers);

  // Se crea el vector solvers
  for (size_t i = 0; i < n_solvers; i++) {
    this->vectorSolverAssemblers[i] =
        new Gold_Solver_Assembler(numbersQueue, numbers_t_queue_resolved);
    this->vectorSolverAssemblers[i]->startThread();
  }
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

bool GoldWebApp::serveHomepage(HttpRequest& httpRequest,
                               HttpResponse& httpResponse) {
  (void)httpRequest;

  // Set HTTP response metadata (headers)
  httpResponse.setHeader("Server", "AttoServer v1.1");
  httpResponse.setHeader("Content-type", "text/html; charset=ascii");

  // Build the body of the response
  std::string title = "Goldbach sums ";
  httpResponse.body()
      << "<!DOCTYPE html>\n"
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
  bool hayError = false;

  // Set HTTP response metadata (headers)
  httpResponse.setHeader("Server", "AttoServer v1.0");
  httpResponse.setHeader("Content-type", "text/html; charset=ascii");

  // Obtener los números del URI
  // if (!getNumbersFromURI(httpRequest, numbersVector, longitud, str)) {
  //   hayError = true;
  // }

  if (!hayError) {
    // sendSuccessResponse(numbersVector, httpResponse);
  } else {
    sendErrorResponse(httpResponse);
  }
  return httpResponse.send();
}

// void GoldWebApp::sendSuccessResponse(const std::vector<int64_t>& numbersVector,
//                                      HttpResponse& httpResponse) {
//   std::string title = " Goldbach Sums";
//   httpResponse.body() << "<!DOCTYPE html>\n"
//                       << "<html lang=\"en\">\n"
//                       << "  <meta charset=\"ascii\"/>\n"
//                       << "  <title>" << title << "</title>\n"
//                       << "  <style>\n"
//                       << "    body {font-family: monospace}\n"
//                       << "    .blue {color: blue}\n"
//                       << "    .small {font-size: 0.8em; color: black}\n"
//                       << "  </style>\n"
//                       << "  <h1>" << title << "</h1>\n";
//   std::vector<int64_t> numbersTemp = numbersVector;

//   GoldSolver goldbach = GoldSolver();
//   NumbersArray_t* numbers = goldbach.resolveGoldbach(numbersTemp);
//   std::vector<std::string> stringSums = create_strings(numbers);

//   for (size_t i = 0; i < numbersVector.size(); i++) {
//     std::string resultado = stringSums[i];
//     httpResponse.body() << " <h1>" << resultado << "</h1>\n";
//   }
//   httpResponse.body() << "</html>\n";
// }

// void GoldWebApp::sendErrorResponse(HttpResponse& httpResponse) {
//   // Build the body for an invalid request
//   std::string title = "Invalid request";
//   httpResponse.body()
//       << "<!DOCTYPE html>\n"
//       << "<html lang=\"en\">\n"
//       << "  <meta charset=\"ascii\"/>\n"
//       << "  <title>" << title << "</title>\n"
//       << "  <style>body {font-family: monospace} .err {color: red}</style>\n"
//       << "  <h1 class=\"err\">" << title << "</h1>\n"
//       << "  <p>Invalid request for Goldbach sums</p>\n"
//       << "  <hr><p><a href=\"/\">Back</a></p>\n"
//       << "</html>\n";
// }

std::vector<std::string> GoldWebApp::create_strings(NumbersArray_t* numbers) {
  std::vector<std::string> sums;
  ///< Cadena temporal para almacenar la suma actual de Goldbach.
  std::string currentSum;
  ///< Arreglo de sumas de Goldbach.
  Numbers_t** SumsArray = numbers->GoldbachSumsArray;
  ///< Variable temporal para almacenar el contador de sumas de Goldbach.
  int64_t n;
  // Itera sobre los números en el arreglo
  for (int64_t i = 0; i < numbers->counterNumbers; i++) {
    currentSum = "";  // Inicializa la cadena actual como vacía
    // Verifica si se deben imprimir las sumas de Goldbach para el número actual
    if (SumsArray[i]->printSums) {
      // Obtiene el contador de sumas de Goldbach para el número actual
      n = SumsArray[i]->sums_counter;
      // Construye la cadena de sumas de Goldbach
      currentSum += "-" + std::to_string(SumsArray[i]->number) + ": " +
                    std::to_string(SumsArray[i]->sums_counter) + " sums: ";
      // Itera sobre las sumas de Goldbach para el número actual
      for (int64_t j = 0; j < n; j++) {
        // Agrega la suma de Goldbach para números pares
        if ((SumsArray[i]->number % 2) == 0) {
          currentSum +=
              "" + std::to_string(SumsArray[i]->goldbachSums[0][j]) + " ";
          currentSum += "+ " + std::to_string(SumsArray[i]->goldbachSums[1][j]);
          if (j == (SumsArray[i]->sums_counter) - 1) {
          } else {
            currentSum += ", ";
          }
          // Agrega la suma de Goldbach para números impares
        } else {
          currentSum +=
              "" + std::to_string(SumsArray[i]->goldbachSums[0][j]) + " ";
          currentSum +=
              "+ " + std::to_string(SumsArray[i]->goldbachSums[1][j]) + " ";
          currentSum += "+ " + std::to_string(SumsArray[i]->goldbachSums[2][j]);
          if (j == (SumsArray[i]->sums_counter) - 1) {
          } else {
            currentSum += ", ";
          }
        }
      }
      // Agrega la cadena de sumas de Goldbach al vector de strings
      sums.push_back(currentSum);

    } else {
      // Construye la cadena para el caso en que
      // no se impriman las sumas de Goldbach
      currentSum += std::to_string(SumsArray[i]->number) + ": " +
                    std::to_string(SumsArray[i]->sums_counter) + " sums";
      // Agrega la cadena al vector de strings
      sums.push_back(currentSum);
    }
  }
  return sums;
}
