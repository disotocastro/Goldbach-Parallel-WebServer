// Copyright 2024 Diego Soto, Migueledo Nuñez, William Moraes
// Universidad de Costa Rica. CC BY 4.0



#include <string>
#include <vector>
#include "FactHTML.hpp"
#include "HttpApp.hpp"
#include "HttpRequest.hpp"
#include "HttpResponse.hpp"
#include "Log.hpp"
#include "Consumer.hpp"
#include "NetworkAddress.hpp"
#include "numbers.hpp"
#include <iostream>
#include <unordered_map>

int FactHTML::run() {
  this->consumeForever();
  return EXIT_SUCCESS;
}

void FactHTML::consume(std::vector<FactNumber*> data_resolved) {
  // Set HTTP response metadata (headers) 
   data_resolved[0]->httpResponse.setHeader("Server", "AttoServer v1.0");
   data_resolved[0]->httpResponse.setHeader("Content-type", "text/html; charset=ascii");

  std::vector<std::string> results = FactorizeToString(data_resolved);
  this->sendSuccessResponse(data_resolved, results);
}

void FactHTML::sendSuccessResponse(std::vector<FactNumber*> data_resolved, const std::vector<std::string>& results) {
  std::string title = "Prime factorization";

  data_resolved[0]->httpResponse.body() << "<!DOCTYPE html>\n"
                      << "<html lang=\"en\">\n"
                      << "  <meta charset=\"ascii\"/>\n"
                      << "  <title>" << title << "</title>\n"
                      << "  <style>\n"
                      << "    body {font-family: monospace}\n"
                      << "    .blue {color: blue}\n"
                      << "    .small {font-size: 0.8em; color: black}\n"
                      << "  </style>\n"
                      << "  <h1>" << title << "</h1>\n";

  for (size_t i = 0; i < data_resolved.size(); i++) {
    std::string numero = std::to_string(data_resolved[0]->numero);
    std::string resultado = results[i];
    data_resolved[0]->httpResponse.body() << "  <h2 class=\"blue\">" << numero
                        << ": <span class=\"small\">" << resultado
                        << "</span></h2>\n";
  }
  data_resolved[0]->httpResponse.body() << "</html>\n";
  data_resolved[0]->httpResponse.send();

}



std::vector<std::string> FactHTML::FactorizeToString(std::vector<FactNumber*> generalFactors) {

  std::vector<std::string> factorizations;

  for (size_t i = 0; i < generalFactors.size(); i++) {
    
    std::vector<int64_t> factors = generalFactors[i]->numbersVector;
    
    // Contar los exponentes de los factores
    std::unordered_map<int64_t, int> exponentCount;
    for (int64_t factor : factors) {
      exponentCount[factor]++;
    }
    // Construir la cadena de factorización
    std::string factorization;
    for (auto index = exponentCount.begin(); index != exponentCount.end();
         ++index) {
      factorization += std::to_string(index->first);
      if (index->second > 1) {
        factorization += "^" + std::to_string(index->second);
      }
      factorization += " * ";
    }
    // Eliminar los últimos caracteres " * " si están presentes
    if (!factorization.empty()) {
      factorization.pop_back();
      factorization.pop_back();
    }

    factorizations.push_back(factorization);
  }
  return factorizations;
}