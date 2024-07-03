// Copyright [2024] <Diego Soto, William Morales, Migueledo Núñez>

#ifndef LOAD_DATA_HPP
#define LOAD_DATA_HPP

#include <fstream>
#include <iostream>
#include <regex>
#include <sstream>
#include <string>
#include <vector>

#include "load_data.hpp"
#include "matrix.hpp"

/**
 * @struct Simulation
 * @brief Estructura que contiene los datos de una simulación de transferencia
 * de calor.
 *
 * Esta estructura almacena todos los parámetros necesarios para realizar una
 * simulación de transferencia de calor, incluyendo la matriz de temperaturas y
 * los parámetros físicos.
 */
struct Simulation {
  Matrix* matrix;  ///< Puntero a la matriz que contiene las temperaturas
  std::string plate_name;      ///< Nombre del archivo de la simulación
  std::string file_name;       ///< Nombre del archivo de la simulación
  double delta_time;           /// < Δtiempo
  double thermal_diffusivity;  ///< Coeficiente de difusividad térmica
  double h;                    ///< Tamaño de la placa
  double sensitivity;          ///< Sensibilidad de la simulación
  int64_t k;
};

/**
 * @brief Carga los datos de simulación desde un archivo.
 *
 * @param file_name Nombre del archivo que contiene los datos de la simulación.
 * @return int Código de retorno. 0 si la carga fue exitosa, otro valor en caso
 * de error.
 *
 * Esta función lee los datos de simulación desde el archivo especificado y los
 * almacena en las estructuras de datos correspondientes.
 */
std::vector<Simulation*> LoadData(std::string file_name);

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
Matrix* read_matrix_from_file(const std::string& file_name);

/**
 * @brief Extrae la ruta base de un archivo de trabajo.
 *
 * Esta función utiliza una expresión regular para extraer la ruta base
 * de un archivo de trabajo, excluyendo el nombre del archivo "jobXXX.txt".
 *
 * @param file_name Nombre completo del archivo, incluyendo la ruta.
 * @return std::string Ruta base del archivo, sin incluir "jobXXX.txt".
 *
 * @example
 * Entrada: "./test/jobs/job001.txt"
 * Salida: "./test/jobs/"
 */
std::string RegexFileRoot(const std::string& file_name);

#endif  // LOAD_DATA_HPP
