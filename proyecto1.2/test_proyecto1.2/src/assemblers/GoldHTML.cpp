// Copyright 2024 Diego Soto, Migueledo Nuñez, William Moraes
// Universidad de Costa Rica. CC BY 4.0



#include <string>
#include <vector>
#include "GoldHTML.hpp"
#include "HttpApp.hpp"
#include "HttpRequest.hpp"
#include "HttpResponse.hpp"
#include "Log.hpp"
#include "Consumer.hpp"
#include "NetworkAddress.hpp"
#include "numbers.hpp"

Gold_HTML::Gold_HTML(Queue<RequestResolved_t*>* request_resolved_queue) {
  this->consumingQueue = request_resolved_queue;
}

int Gold_HTML::run() {
  this->consumeForever();
  return EXIT_SUCCESS;
}

void Gold_HTML::consume(RequestResolved_t* resolved) {
  sendSuccessResponse(resolved);
  HttpResponse response = resolved->GoldbachSumsArray[0]->httpResponse;
  // Set HTTP response metadata (headers)
  response.setHeader("Server", "AttoServer v1.0");
  response.setHeader("Content-type", "text/html; charset=ascii");
}

std::vector<std::string> Gold_HTML::create_strings(RequestResolved_t* numbers) {
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

void Gold_HTML::sendSuccessResponse(RequestResolved_t* resolved) {
  
  HttpResponse response = resolved->GoldbachSumsArray[0]->httpResponse;

  std::string title = " Goldbach Sums";
  response.body() << "<!DOCTYPE html>\n"
                      << "<html lang=\"en\">\n"
                      << "  <meta charset=\"ascii\"/>\n"
                      << "  <title>" << title << "</title>\n"
                      << "  <style>\n"
                      << "    body {font-family: monospace}\n"
                      << "    .blue {color: blue}\n"
                      << "    .small {font-size: 0.8em; color: black}\n"
                      << "  </style>\n"
                      << "  <h1>" << title << "</h1>\n";


  std::vector<std::string> stringSums = create_strings(resolved);

  for (size_t i = 0; i < resolved->maxNumbers; i++) {
    std::string resultado = stringSums[i];
    response.body() << " <h1>" << resultado << "</h1>\n";
  }
  response.body() << "</html>\n";
}




// void GoldHTML::sendErrorResponse(HttpResponse& httpResponse) {
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

//   // return httpResponse.send();
// }
