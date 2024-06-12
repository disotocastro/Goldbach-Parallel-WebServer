// Copyright 2024 Diego Soto, Migueledo Nuñez, William Morales
// Universidad de Costa Rica. CC BY 4.0

#ifndef FACTNUMBER_HPP
#define FACTNUMBER_HPP

#include <vector>


#include "HttpResponse.hpp"

/**
 * @class FactNumber
 * @brief Clase que representa un número a ser factorizado junto con sus
 * metadatos y respuesta HTTP.
 *
 * Esta clase contiene el número a ser factorizado, su identificador, índice,
 * máximo de números, y un vector para almacenar los resultados de la
 * factorización. También incluye una respuesta HTTP asociada.
 */
class FactNumber {
 public:
  /**
   * @brief Vector que almacena los factores del número.
   */
  std::vector<int64_t> numbersVector;
  /**
   * @brief Respuesta HTTP asociada con la solicitud de factorización.
   */
  HttpResponse httpResponse;
  /**
   * @brief Identificador único del objeto FactNumber.
   */
  int64_t id;
  /**
   * @brief Índice del objeto FactNumber en una colección o proceso.
   */
  int64_t index;
  /**
   * @brief Número a ser factorizado.
   */
  int64_t numero;
  /**
   * @brief Máximo número de factores permitidos.
   */
  int64_t maxNumbers;

  /**
   * @brief Constructor de la clase FactNumber.
   *
   * Inicializa un nuevo objeto FactNumber con los parámetros proporcionados.
   *
   * @param response Respuesta HTTP asociada.
   * @param id Identificador único del objeto FactNumber.
   * @param index Índice del objeto FactNumber.
   * @param numero Número a ser factorizado.
   * @param maxNumbers Máximo número de factores permitidos.
   */
  FactNumber(HttpResponse response, int64_t id, int64_t index, int64_t numero,
             int64_t maxNumbers)
      : httpResponse(response),
        id(id),
        index(index),
        numero(numero),
        maxNumbers(maxNumbers) {}
};

#endif  // FACTNUMBER_HPP

