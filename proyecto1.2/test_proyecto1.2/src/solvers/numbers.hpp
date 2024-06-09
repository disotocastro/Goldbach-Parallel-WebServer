// Copyright 2024 William Morales <william.moralesfuentes@ucr.ac.cr>

#ifndef NUMBERS_HPP
#define NUMBERS_HPP

#include <cstdint>
#include <vector>

#include "HttpResponse.hpp"

/**
 * @brief Estructura para representar un número y sus sumas de Goldbach.
 */
typedef struct {
  bool printSums; /**< Indicador de impresión de sumas */
  int64_t id;
  int64_t index;
  int64_t number; /**< El número */
  int64_t maxNumbers;
  int64_t sums_counter;   /**< Cantidad de sumas de Goldbach */
  int64_t** goldbachSums; /**< Matriz de sumas de Goldbach */
  HttpResponse httpResponse;

} Numbers_t;

/**
 * @brief Estructura para representar una lista de números y sus sumas
 * de Goldbach.
 */
class RequestResolved_t {
 public:
  RequestResolved_t(){};

  RequestResolved_t(int64_t ID, int64_t maxNumbers) {
    this->id = ID;
    this->maxNumbers = maxNumbers;
  }

  ~RequestResolved_t() {}

  Numbers_t** GoldbachSumsArray; /**< Arreglo de punteros a estructuras */
  int64_t counterNumbers;        /**< Número total de números en la lista */
  int64_t totalSums;             /**< Número total de sumas en la lista */
  int64_t id;
  int64_t maxNumbers;
};

/**
 * @brief Libera la memoria asignada a la lista de números.
 * @param NumbersArray Puntero a la estructura NumbersArray_t
 * que contiene los números.
 */
void free_memory();

#endif
