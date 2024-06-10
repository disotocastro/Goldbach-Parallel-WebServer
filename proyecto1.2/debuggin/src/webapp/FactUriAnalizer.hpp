// Copyright 2024 Diego Soto, Migueledo Nuñez, William Moraes
// Universidad de Costa Rica. CC BY 4.0

#ifndef FACTURIANALIZER_HPP
#define FACTURIANALIZER_HPP

#include <vector>

#include "Assembler.hpp"
#include "HttpApp.hpp"
#include "HttpRequest.hpp"
#include "HttpResponse.hpp"
#include "Queue.hpp"
#include "RequestResponseStruct.hpp"
#include "Socket.hpp"

class FactUriAnalizer
    : public Assembler<RequestResponseStruct_t, RequestResponseStruct_t> {
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
  void consume(RequestResponseStruct_t data) override;

  bool serveHomepage(HttpRequest& httpRequest, HttpResponse& httpResponse);
};

#endif  // FACTURIANALIZER_HPP
