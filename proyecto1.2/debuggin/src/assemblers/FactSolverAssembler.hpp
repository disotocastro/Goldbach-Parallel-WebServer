// Copyright 2024 Diego Soto, Migueledo Nuñez, William Morales
// Universidad de Costa Rica. CC BY 4.0

#ifndef FACTSOLVERASSEMBLER_HPP
#define FACTSOLVERASSEMBLER_HPP

#include <string>
#include <vector>

#include "Assembler.hpp"
#include "FactNumber.hpp"
#include "HttpApp.hpp"
#include "HttpRequest.hpp"
#include "HttpResponse.hpp"
#include "Queue.hpp"
#include "RequestResponseStruct.hpp"
#include "Socket.hpp"

class FactSolverAssembler : public Assembler<FactNumber*, FactNumber*> {
 public:
  /**
   * @brief Método para ejecutar la conexión HTTP.
   * @return Entero que indica el estado de la ejecución.
   */
  int run() override;

  /**
   * @brief Método para consumir un socket.
   * @param client Socket que se va a consumir.
   */
  void consume(FactNumber* data) override;

  //FactSolverAssembler();

  bool serveFactorize(HttpResponse& httpResponse, std::string cadena);

  std::string buildString (std::vector<int64_t> numbersVector);

};

#endif  // FACTSOLVERASSEMBLER_HPP
