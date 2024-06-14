// Copyright 2024 Diego Soto, Migueledo Nuñez, William Morales
// Universidad de Costa Rica. CC BY 4.0

#ifndef REQUESTRESPONSESTRUCTS_HPP
#define REQUESTRESPONSESTRUCTS_HPP

#include "HttpRequest.hpp"
#include "HttpResponse.hpp"

/**
 * @struct RequestResponseStruct
 * @brief Estructura que encapsula una solicitud HTTP y su respuesta asociada.
 *
 * Esta estructura contiene un objeto HttpRequest que representa la solicitud
 * HTTP y un objeto HttpResponse que representa la respuesta HTTP.
 */
typedef struct RequestResponseStruct {
  /**
   * @brief Solicitud HTTP.
   */
  HttpRequest httpRequest;
  /**
   * @brief Respuesta HTTP.
   */
  HttpResponse httpResponse;

  int stopCondition;

 public:
  /**
   * @brief Constructor con parámetros por defecto.
   *
   * Inicializa un nuevo objeto RequestResponseStruct con objetos HttpRequest y
   * HttpResponse creados con sockets por defecto.
   *
   * @param request Objeto HttpRequest para la solicitud (por defecto, un
   * HttpRequest con Socket por defecto).
   * @param response Objeto HttpResponse para la respuesta (por defecto, un
   * HttpResponse con Socket por defecto).
   */
  RequestResponseStruct(HttpRequest request = HttpRequest((Socket())),
                        HttpResponse response = HttpResponse((Socket())))
      : httpRequest(request), httpResponse(response), stopCondition(0) {}

  /**
   * @brief Operador de igualdad.
   *
   * Compara dos objetos RequestResponseStruct para verificar si son iguales.
   *
   * @param other Otro objeto RequestResponseStruct a comparar.
   * @return true si ambos objetos son iguales, false en caso contrario.
   */
  inline bool operator==(const RequestResponseStruct& other) const {
    return this->httpRequest == other.httpRequest &&
           this->httpResponse == other.httpResponse;
  }
} RequestResponseStruct_t;

#endif  // REQUESTRESPONSESTRUCTS_HPP
