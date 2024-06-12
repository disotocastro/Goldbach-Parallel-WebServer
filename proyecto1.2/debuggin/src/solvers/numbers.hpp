// Copyright 2024 William Morales <william.moralesfuentes@ucr.ac.cr>

#ifndef NUMBERS_HPP
#define NUMBERS_HPP

#include <cstdint>

#include "HttpResponse.hpp"

class Numbers_t {
 public:
  
  bool printSums; /**< Indicador de impresión de sumas */
  int64_t id;
  int64_t index;
  int64_t number; /**< El número */
  int64_t maxNumbers;
  int64_t sums_counter;   /**< Cantidad de sumas de Goldbach */
  int64_t** goldbachSums; /**< Matriz de sumas de Goldbach */
  HttpResponse httpResponse;


  Numbers_t(int64_t id, int64_t index, int64_t number, int64_t maxNumbers, HttpResponse httpResponse)
      : id(id),
        index(index),
        number(number),
        maxNumbers(maxNumbers),
        sums_counter(0),
        printSums(false),
        goldbachSums(nullptr),
        httpResponse(httpResponse) {

          if (this->number < 0)
          {
            this->printSums = true;
            this->number = -number;
          }
          


        }
};


#endif
