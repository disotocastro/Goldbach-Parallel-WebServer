// Copyright [2024] <Diego Soto, William Morales, Migueledo Núñez>

#ifndef REPORT_HPP
#define REPORT_HPP

#include <cstdio>
#include <ctime>
#include <matrix.hpp>
#include <simulation.hpp>
#include <string>
#include <vector>

/**
 * @file report.hpp
 * @brief Contiene funciones para generar reportes y manipular archivos
 * relacionados con simulaciones.
 */

/**
 * @brief Genera un reporte a partir de un vector de simulaciones.
 *
 * Esta función crea un archivo de reporte en formato TSV con información de las
 * simulaciones proporcionadas.
 *
 * @param simulations Vector de punteros a objetos Simulation.
 */
void Report(std::vector<Simulation*> simulations);

/**
 * @brief Formatea un tiempo dado en segundos a una cadena legible para humanos.
 *
 * @param seconds Tiempo en segundos.
 * @return std::string Cadena formateada con el tiempo en formato "YYYY/MM/DD
 * hh:mm:ss".
 */
std::string format_time(const time_t seconds);

/**
 * @brief Guarda una matriz en un archivo binario.
 *
 * @param matrix Puntero a la matriz a guardar.
 * @param original_plate_name Nombre original de la placa.
 * @param k Número de iteración.
 */
void save_matrix_to_file(const Matrix* matrix,
                         const std::string& original_plate_name, int64_t k);

/**
 * @brief Genera un nuevo nombre de archivo para una placa basado en el nombre
 * original y el número de iteración.
 *
 * @param original_plate_name Nombre original de la placa.
 * @param k Número de iteración.
 * @return std::string Nuevo nombre de archivo.
 */
std::string RegexPlatename(const std::string& original_plate_name, int64_t k);

/**
 * @brief Extrae el nombre base de un archivo de trabajo y le agrega la
 * extensión .tsv.
 *
 * @param file_name Nombre del archivo de trabajo.
 * @return std::string Nombre base del archivo con la extensión .tsv.
 */
std::string RegexTabName(const std::string& file_name);

#endif  // REPORT_HPP
