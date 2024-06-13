
//  @copyright 2024 Diego Soto, Migueledo Nuñez, William Morales
//  Universidad de Costa Rica. CC BY 4.0

#ifndef GOLDURIANALIZER_HPP
#define GOLDURIANALIZER_HPP

#include <cstdint>
#include <regex>
#include <string>
#include <vector>

#include "Assembler.hpp"
#include "HttpRequest.hpp"
#include "HttpResponse.hpp"
#include "RequestResponseStruct.hpp"
#include "numbers.hpp"

/**
 * @class GoldUriAnalizer
 * @brief Clase que analiza y maneja las peticiones URI para las sumas de
 * Goldbach de los números
 */
class GoldUriAnalizer : public Assembler<RequestResponseStruct_t, Numbers_t*> {
 public:
  /// @brief ID para los elementos de la cola de producción.
  int64_t Element_ID = 0;

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
   * @param httpRequest solicitud HTTP.
   * @param httpResponse respuesta HTTP.
   * @return `true` si la respuesta se envía con éxito, `false` en caso
   * contrario.
   */
  bool serveHomepage(HttpRequest& httpRequest, HttpResponse& httpResponse);

  /**
   * @brief Envía una respuesta de error al cliente.
   * @param httpResponserespuesta HTTP.
   */
  void sendErrorResponse(HttpResponse& httpResponse);

  /**
   * @brief Obtiene los números de una URI.
   * @param httpRequest solicitud HTTP.
   * @return Vector de números obtenidos de la URI.
   */
  std::vector<int64_t> getNumbersFromURI(HttpRequest& httpRequest);

  /**
   * @brief Método para realizar las sumas Goldbach.
   * @param data Estructura que contiene los datos de la petición y la respuesta
   * HTTP.
   */
  void GoldBach(RequestResponseStruct_t data);

  /**
   * @brief Lee los números de la entrada y los almacena en una lista para su
   * procesamiento.
   * @param inputNumbers Vector de números a procesar.
   * @param reqRes Estructura que contiene los datos de la petición y la
   * respuesta HTTP.
   */
  void readNumbers(std::vector<int64_t>& inputNumbers,
                   RequestResponseStruct_t reqRes);
};

#endif  // GOLDURIANALIZER_HPP
