// Copyright 2024 Diego Soto, Migueledo Nuñez, William Moraes
// Universidad de Costa Rica. CC BY 4.0

#include "GoldHTML.hpp"

#include <string>
#include <vector>

#include "Consumer.hpp"
#include "HttpApp.hpp"
#include "HttpRequest.hpp"
#include "HttpResponse.hpp"
#include "Log.hpp"
#include "NetworkAddress.hpp"
#include "numbers.hpp"

int GoldHTML::run() {
  this->consumeForever();
  return EXIT_SUCCESS;
}

void GoldHTML::consume(std::vector<Numbers_t*> data) {
  sendSuccessResponse(data);
  HttpResponse response = data[0]->httpResponse;

  // Set HTTP response metadata (headers)
  response.setHeader("Server", "AttoServer v1.0");
  response.setHeader("Content-type", "text/html; charset=ascii");
}

std::vector<std::string> GoldHTML::create_strings(std::vector<Numbers_t*>  numbers) {
  std::vector<std::string> sums;
  ///< Cadena temporal para almacenar la suma actual de Goldbach.
  std::string currentSum;

  ///< Variable temporal para almacenar el contador de sumas de Goldbach.
  int64_t n;
  // Itera sobre los números en el arreglo
  for (int64_t i = 0; i < numbers[0]->maxNumbers; i++) {
    currentSum = "";  // Inicializa la cadena actual como vacía
    // Verifica si se deben imprimir las sumas de Goldbach para el número actual
    if (numbers[i]->printSums) {
      // Obtiene el contador de sumas de Goldbach para el número actual
      n = numbers[i]->sums_counter;
      // Construye la cadena de sumas de Goldbach
      currentSum += "-" + std::to_string(numbers[i]->number) + ": " +
                    std::to_string(numbers[i]->sums_counter) + " sums: ";
      // Itera sobre las sumas de Goldbach para el número actual
      for (int64_t j = 0; j < n; j++) {
        // Agrega la suma de Goldbach para números pares
        if ((numbers[i]->number % 2) == 0) {
          currentSum +=
              "" + std::to_string(numbers[i]->goldbachSums[0][j]) + " ";
          currentSum += "+ " + std::to_string(numbers[i]->goldbachSums[1][j]);
          if (j == (numbers[i]->sums_counter) - 1) {
          } else {
            currentSum += ", ";
          }
          // Agrega la suma de Goldbach para números impares
        } else {
          currentSum +=
              "" + std::to_string(numbers[i]->goldbachSums[0][j]) + " ";
          currentSum +=
              "+ " + std::to_string(numbers[i]->goldbachSums[1][j]) + " ";
          currentSum += "+ " + std::to_string(numbers[i]->goldbachSums[2][j]);
          if (j == (numbers[i]->sums_counter) - 1) {
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
      currentSum += std::to_string(numbers[i]->number) + ": " +
                    std::to_string(numbers[i]->sums_counter) + " sums";
      // Agrega la cadena al vector de strings
      sums.push_back(currentSum);
    }
  }
  return sums;
}

void GoldHTML::sendSuccessResponse(std::vector<Numbers_t*> numbers) {
  HttpResponse response = numbers[0]->httpResponse;

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

  std::vector<std::string> stringSums = create_strings(numbers);

  for (int64_t i = 0; i < numbers[0]->maxNumbers; i++) {
    std::string resultado = stringSums[i];
    response.body() << " <h1>" << resultado << "</h1>\n";
  }

  response.body() 
  << "  <hr><p><a href=\"/gold\">Back</a></p>\n"
  << "</html>\n";
  response.send();
}
