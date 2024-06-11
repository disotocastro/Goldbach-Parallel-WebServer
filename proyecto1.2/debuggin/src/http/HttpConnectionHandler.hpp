// Copyright 2024 Diego Soto, Migueledo Nuñez, William Morales
// Universidad de Costa Rica. CC BY 4.0

#ifndef HTTPCONNECTIONHANDLER_HPP
#define HTTPCONNECTIONHANDLER_HPP

#include <vector>

#include "Assembler.hpp"
#include "HttpApp.hpp"
#include "RequestResponseStruct.hpp"
#include "Socket.hpp"

/**
 * @class HttpConnectionHandler
 * @brief Clase para manejar conexiones HTTP.
 *
 * La clase HttpConnectionHandler maneja conexiones HTTP utilizando un conjunto
 * de aplicaciones web registradas. Hereda de Consumer<Socket> y proporciona
 * métodos para consumir sockets y manejar peticiones HTTP.
 */
class HttpConnectionHandler
    : public Assembler<Socket, RequestResponseStruct_t> {
 public:
  /**
   * @brief Constructor de la clase HttpConnectionHandler.
   * @param WebApps Puntero a un vector de punteros a objetos HttpApp.
   */
  HttpConnectionHandler();

  /**
   * @brief Método para ejecutar la conexión HTTP.
   * @return Entero que indica el estado de la ejecución.
   */
  int run() override;

  /**
   * @brief Método para consumir un socket.
   * @param client Socket que se va a consumir.
   */
  void consume(Socket client) override;
};

#endif  // HTTPCONNECTIONHANDLER_HPP
