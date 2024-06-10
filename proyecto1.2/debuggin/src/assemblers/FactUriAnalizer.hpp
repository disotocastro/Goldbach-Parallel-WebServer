// Copyright 2024 Diego Soto, Migueledo Nuñez, William Morales
// Universidad de Costa Rica. CC BY 4.0

#ifndef FACTURIANALIZER_HPP
#define FACTURIANALIZER_HPP

#include <vector>
#include <string>

#include "Assembler.hpp"
#include "HttpApp.hpp"
#include "HttpRequest.hpp"
#include "HttpResponse.hpp"
#include "Queue.hpp"
#include "RequestResponseStruct.hpp"
#include "Socket.hpp"
#include "FactNumber.hpp"


class FactUriAnalizer
    : public Assembler<RequestResponseStruct_t, FactNumber*> {
 public:

  /// @brief ID para los elementos de la cola de produccion
  int64_t Element_ID = 0;

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
  bool serveFactorize(HttpRequest& httpRequest
  , HttpResponse& httpResponse, std::string cadena);

   /**
   * @brief Fill a vector of integers from a string representation.
   * @param numbersString The string containing numbers separated by spaces.
   * @return A vector of integers.
   */
  std::vector<int64_t> fillVector(std::string numbersString);

  void factUri(HttpRequest& httpRequest, HttpResponse& httpResponse);
};

#endif  // FACTURIANALIZER_HPP
