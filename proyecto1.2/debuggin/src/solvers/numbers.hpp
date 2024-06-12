// Copyright 2024 William Morales <william.moralesfuentes@ucr.ac.cr>

#ifndef NUMBERS_HPP
#define NUMBERS_HPP

#include <cstdint>

#include "HttpResponse.hpp"

/**
 * @class Numbers_t
 * @brief Clase que representa números y sus sumas de Goldbach.
 *
 * Esta clase almacena un número y maneja sus sumas de Goldbach, así como
 * la respuesta HTTP relacionada.
 */
class Numbers_t {
 public:
  int64_t id;           /**< Identificador del número */
  int64_t index;        /**< Índice del número */
  int64_t number;       /**< El número */
  int64_t maxNumbers;   /**< Número máximo de sumas de Goldbach a almacenar */
  int64_t sums_counter; /**< Cantidad de sumas de Goldbach */
  int64_t** goldbachSums;    /**< Matriz de sumas de Goldbach */
  bool printSums;       /**< Indicador de impresión de sumas */
  HttpResponse httpResponse; /**< Respuesta HTTP asociada */

  /**
   * @brief Constructor de la clase Numbers_t.
   *
   * @param id Identificador del número.
   * @param index Índice del número.
   * @param number El número.
   * @param maxNumbers Número máximo de sumas de Goldbach a almacenar.
   * @param httpResponse Respuesta HTTP asociada.
   */
  Numbers_t(int64_t id, int64_t index, int64_t number, int64_t maxNumbers,
            HttpResponse httpResponse)
      : id(id),
        index(index),
        number(number),
        maxNumbers(maxNumbers),
        sums_counter(0),
        goldbachSums(nullptr),
        printSums(false),
        httpResponse(httpResponse) {
    if (this->number < 0) {
      this->printSums = true;
      this->number = -number;
    }
  }
};

#endif
