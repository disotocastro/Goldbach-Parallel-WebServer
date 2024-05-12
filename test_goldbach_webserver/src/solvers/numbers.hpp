// Copyright 2024 William Morales <william.moralesfuentes@ucr.ac.cr>

#ifndef NUMBERS_HPP
#define NUMBERS_HPP

#include <cstdint> 


/**
 * @brief Estructura para representar un número y sus sumas de Goldbach.
 */
typedef struct  {
  int64_t number;             /**< El número */
  int64_t** goldbachSums;     /**< Matriz de sumas de Goldbach */
  int64_t sums_counter;       /**< Cantidad de sumas de Goldbach */
  bool printSums;             /**< Indicador de impresión de sumas */
} Numbers_t;

/**
 * @brief Estructura para representar una lista de números y sus sumas 
 * de Goldbach.
 */
typedef struct {
  Numbers_t** GoldbachSumsArray; /**< Arreglo de punteros a estructuras */
  int64_t counterNumbers;        /**< Número total de números en la lista */
  int64_t largestNumber;         /**< El número más grande en la lista */
  int64_t totalSums;             /**< Número total de sumas en la lista */
  int64_t counterPrimes;         /**< Número total de números primos */
  int64_t* primeNumbers;         /**< Arreglo de números primos */
} NumbersArray_t;

/**
 * @brief Crea una nueva estructura Numbers_t con el número especificado.
 * @param newNumber El número para crear la estructura.
 * @return Puntero a la nueva estructura Numbers_t creada.
 */
Numbers_t* new_number(int64_t newNumber);


/**
 * @brief Lee los números de la entrada estándar y los almacena en un arreglo.
 * @return Puntero a la estructura NumbersArray_t que contiene los números leídos.
 */
NumbersArray_t* readNumbers(int64_t* inputNumbers, int64_t numberArraySize);

/**
 * @brief Libera la memoria asignada a la lista de números.
 * @param NumbersArray Puntero a la estructura NumbersArray_t que contiene los números.
 */
void free_memory(NumbersArray_t* numbers);

#endif
