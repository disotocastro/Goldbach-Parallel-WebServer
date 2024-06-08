// Copyright 2024 William Morales <william.moralesfuentes@ucr.ac.cr>

#ifndef GOLDSOLVER_HPP
#define GOLDSOLVER_HPP

#include <cstdint>
#include <numbers.hpp>
#include <string>
#include <vector>

/**
 * @class GoldSolver
 * @brief Clase para resolver la conjetura de Goldbach.
 *
 * La clase GoldSolver proporciona métodos para encontrar números primos,
 * y para calcular las sumas de Goldbach para números pares e impares.
 */
class GoldSolver {
 public:
  /**
   * @brief Constructor para GoldSolver.
   */
  GoldSolver();
  /**
   * @brief Destructor para GoldSolver.
   */
  ~GoldSolver();

  /**
   * @brief Encuentra los números primos hasta
   * el número más grande en la lista.
   * @param NumbersArray Puntero a la estructura NumbersArray_t
   * que contiene los números.
   */
  std::vector<int64_t> prime_numbers(int64_t number);

  /**
   * @brief Calcula las sumas de Goldbach para números impares.
   * @param NumbersArray Puntero a la estructura NumbersArray_t
   * que contiene los números.
   * @param index Índice del número en el arreglo.
   */
  void goldbach_odd(Numbers_t* inputNumber, std::vector<int64_t> primeNumbers);

  /**
   * @brief Calcula las sumas de Goldbach para números pares.
   * @param NumbersArray Puntero a la estructura NumbersArray_t
   * que contiene los números.
   * @param index Índice del número en el arreglo.
   */
  void goldbach_pair(Numbers_t* inputNumber, std::vector<int64_t> primeNumbers);

  /**
   * @brief Resuelve la conjetura de Goldbach para un conjunto de números de
   * entrada.
   *
   * @param inputNumbers Vector que contiene los números de entrada.
   * @return Puntero a la estructura NumbersArray_t que contiene los resultados.
   */
  void resolveGoldbach(Numbers_t* inputNumber);
};

#endif
