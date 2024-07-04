#include <iostream>

#include "matrix.hpp"

/**
 * @brief Lee una matriz desde un archivo binario.
 *
 * @param file_name Nombre del archivo binario que contiene la matriz.
 * @return Matrix* Puntero a la matriz leída. Retorna nullptr en caso de error.
 *
 * Esta función lee una matriz de temperaturas desde un archivo binario con un
 * formato específico. El archivo debe contener primero las dimensiones de la
 * matriz (filas y columnas) seguidas por los datos de la matriz.
 */
Matrix* read_matrix_from_file(const std::string& plate_name);