// Copyright [2024] <Diego Soto, William Morales, Migueledo Núñez>

#ifndef SIMULATION_HPP
#define SIMULATION_HPP

#include <vector>
#include <load_data.hpp>
#include <matrix.hpp>


/**
 * @brief Inicia todas las simulaciones en el vector proporcionado.
 * @param simulations Vector de punteros a objetos Simulation.
 */
void StartSimulation(std::vector<Simulation*> simulations);

/**
 * @brief Ejecuta una simulación individual de manera completa.
 * @param sim Puntero al objeto Simulation a ejecutar.
 */
void RunSimulation(Simulation* sim);

/**
 * @brief Calcula el valor de calor un punto en la simulación para la siguiente
 * iteración.
 * @param sim Puntero al objeto Simulation.
 * @param row Índice de fila del punto.
 * @param col Índice de columna del punto.
 * @return Nuevo valor calculado para el punto.
 */
double CaculateSimulation(Simulation* sim, int64_t row, int64_t col);

#endif  // SIMULATION_HPP
