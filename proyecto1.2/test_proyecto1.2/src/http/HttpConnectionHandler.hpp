// Copyright 2024 Diego Soto, Migueledo Nuñez, William Moraes
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
class HttpConnectionHandler : public Assembler<Socket, RequestResponseStruct> {
 public:
  /**
   * @brief Constructor de la clase HttpConnectionHandler.
   * @param WebApps Puntero a un vector de punteros a objetos HttpApp.
   */
  explicit HttpConnectionHandler(std::vector<HttpApp*>* WebApps);

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

  /// Route, that provide an answer according to the URI value
  /// For example, home page is handled different than a number
  bool route(HttpRequest& httpRequest, HttpResponse& httpResponse);

  /// Sends a page for a non found resouce in this server. This method is called
  /// if none of the registered web applications handled the request.
  /// If you want to override this method, create a web app, e.g NotFoundWebApp
  /// that reacts to all URIs, and chain it as the last web app
  bool serveNotFound(HttpRequest& httpRequest, HttpResponse& httpResponse);

  /// Called each time an HTTP request is received. Web server should analyze
  /// the request object and assemble a response with the response object.
  /// Finally send the response calling the httpResponse.send() method.
  /// @return true on success and the server will continue handling further
  /// HTTP requests, or false if server should stop accepting requests from
  /// this client (e.g: HTTP/1.0)
  virtual bool handleHttpRequest(HttpRequest& httpRequest,
                                 HttpResponse& httpResponse);

 protected:
  /// Puntero a un vector de punteros a objetos HttpApp.
  std::vector<HttpApp*>* applications;
};

#endif  // HTTPCONNECTIONHANDLER_HPP
