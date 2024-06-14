// Copyright 2024 Diego Soto, Migueledo Nuñez, William Morales
// Universidad de Costa Rica. CC BY 4.0

#ifndef FACTURIANALIZER_HPP
#define FACTURIANALIZER_HPP

#include <string>
#include <vector>

#include "Assembler.hpp"
#include "FactNumber.hpp"
#include "HttpRequest.hpp"
#include "HttpResponse.hpp"
#include "RequestResponseStruct.hpp"

/**
 * @class FactUriAnalizer
 * @brief Clase que analiza y maneja las peticiones URI para la
 * factorización de números.
 */
class FactUriAnalizer : public Assembler<RequestResponseStruct_t, FactNumber*> {
 public:
  /// @brief ID para los elementos de la cola de producción.
  int64_t Element_ID = 0;

  int64_t maxSolvers = std::thread::hardware_concurrency();

  /**
   * @brief Método para ejecutar la conexión HTTP.
   * @return Entero que indica el estado de la ejecución.
   */
  int run() override;

  /**
   * @brief Método para consumir una estructura de datos de petición y
   * respuesta.
   * @param data Estructura que contiene los datos de la petición y la respuesta
   * HTTP.
   */
  void consume(RequestResponseStruct_t data) override;

  /**
   * @brief Sirve la página principal del servidor HTTP.
   * @param httpRequest Objeto que representa la solicitud HTTP.
   * @param httpResponse Objeto que representa la respuesta HTTP.
   * @return `true` si la respuesta se envía con éxito, `false` en caso
   * contrario.
   */
  bool serveHomepage(HttpRequest& httpRequest, HttpResponse& httpResponse);

  /**
   * @brief Sirve la página de factorización.
   * @param httpRequest Objeto que representa la solicitud HTTP.
   * @param httpResponse Objeto que representa la respuesta HTTP.
   * @param cadena Cadena de texto que contiene los números a factorizar.
   * @return `true` si la respuesta se envía con éxito, `false` en caso
   * contrario.
   */
  bool serveFactorize(HttpRequest& httpRequest, HttpResponse& httpResponse,
                      std::string cadena);

  /**
   * @brief Llena un vector de enteros a partir de una representación en cadena.
   * @param numbersString Cadena de texto que contiene los números separados por
   * espacios.
   * @return Un vector de enteros.
   */
  std::vector<int64_t> fillVector(std::string numbersString);

  /**
   * @brief Analiza la URI y procesa la solicitud de factorización.
   * @param data Estructura que contiene los datos de la petición y la respuesta
   * HTTP.
   * @param pos Posición en la URI donde comienza la cadena de números.
   */
  void factUri(RequestResponseStruct_t data, size_t pos);

  /**
   * @brief Envía una respuesta de error al cliente.
   * @param httpResponse Objeto que representa la respuesta HTTP.
   */
  void sendErrorResponse(HttpResponse& httpResponse);

  void consumeForever() override;
};

#endif  // FACTURIANALIZER_HPP
