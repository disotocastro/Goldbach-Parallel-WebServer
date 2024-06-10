// Copyright 2024 Diego Soto, Migueledo Nuñez, William Morales
// Universidad de Costa Rica. CC BY 4.0
#include <string>
#include <vector>

#include "FactUriAnalizer.hpp"
#include "FactNumber.hpp"
#include "FactSolverAssembler.hpp"
#include "FactSolver.hpp"
#include "HttpApp.hpp"
#include "HttpRequest.hpp"
#include "HttpResponse.hpp"
#include "Log.hpp"
#include "NetworkAddress.hpp"


int FactSolverAssembler::run() {
  this->consumeForever();
  return EXIT_SUCCESS;
}

void FactSolverAssembler::consume(FactNumber* data) {
  FactSolver solver = FactSolver();
  data->numbersVector = solver.FactorizeVector(data->numero);
  //std::string cadena = buildString(data->numbersVector);
  // this->serveFactorize(data->httpResponse, cadena);
  produce(data);
}

// std::string FactSolverAssembler::buildString (std::vector<int64_t> numbersVector){
//   std::string cadena = "";

//   for (size_t i = 0; i < numbersVector.size(); i++){
//     cadena += ", "+std::to_string(numbersVector[i]);
//   }
  
//   return cadena;
// }


// bool FactSolverAssembler::serveFactorize(HttpResponse& httpResponse, std::string cadena) {

//   // Set HTTP response metadata (headers)
//   httpResponse.setHeader("Server", "AttoServer v1.1");
//   httpResponse.setHeader("Content-type", "text/html; charset=ascii");

//   // Build the body of the response
//   std::string title = "Prime factorization of ";
//   httpResponse.body() << "<!DOCTYPE html>\n"
//     << "<html lang=\"en\">\n"
//     << "  <meta charset=\"ascii\"/>\n"
//     << "  <title>" << title << "</title>\n"
//     << "  <style>body {font-family: monospace}</style>\n"
//     << "  <h1>" << cadena << "</h1>\n"
//     << "  <hr><p><a href=\"/fact\">Back</a></p>\n"
//     << "</html>\n";

//   // Send the response to the client (user agent)
//   return httpResponse.send();
// }


