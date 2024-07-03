// Copyright [2024] <Diego Soto, William Morales, Migueledo Núñez>

#ifndef MATRIX_HPP
#define MATRIX_HPP

#include <fstream>
#include <iostream>
#include <string>

/**
 * @class Matrix
 * @brief Representa una matriz bidimensional de números de punto flotante.
 *
 * Esta clase proporciona una implementación básica de una matriz 2D
 * utilizando memoria dinámica para almacenar los datos.
 */
class Matrix {
 public:
  int64_t rows;   ///< Número de filas en la matriz
  int64_t cols;   ///< Número de columnas en la matriz
  double** data;  ///< Puntero a puntero que almacena los datos de la matriz

  /**
   * @brief Constructor por defecto.
   *
   * Inicializa una matriz vacía con 0 filas, 0 columnas y sin datos.
   */
  Matrix() : rows(0), cols(0), data(nullptr) {}

  /**
   * @brief Constructor parametrizado.
   *
   * @param r Número de filas de la matriz.
   * @param c Número de columnas de la matriz.
   *
   * Crea una matriz con las dimensiones especificadas y asigna memoria para los
   * datos.
   */
  Matrix(int64_t r, int64_t c) : rows(r), cols(c) {
    data = new double*[rows];
    for (int64_t i = 0; i < rows; ++i) {
      data[i] = new double[cols];
    }
  }

  /**
   * @brief Destructor.
   *
   * Libera la memoria asignada para los datos de la matriz.
   */
  ~Matrix() {
    if (data) {
      for (int64_t i = 0; i < rows; ++i) {
        delete[] data[i];
      }
      delete[] data;
    }
  }
};

#endif  // MATRIX_HPP
