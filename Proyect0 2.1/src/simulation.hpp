#ifndef SIMULATION_HPP
#define SIMULATION_HPP

#include <load_data.hpp>
#include <matrix.hpp>

/**
 * @brief Inicia todas las simulaciones en el vector proporcionado.
 * @param simulations Vector de punteros a objetos Simulation.
 */
void Start_Simulations(std::vector<Simulation*> simulations);

/**
 * @brief Ejecuta una simulación individual de manera completa.
 * @param sim Puntero al objeto Simulation a ejecutar.
 */
void Run_Simulation(Simulation* sim);

/**
 * @brief Calcula el valor de calor un punto en la simulación para la siguiente
 * iteración.
 * @param sim Puntero al objeto Simulation.
 * @param row Índice de fila del punto.
 * @param col Índice de columna del punto.
 * @return Nuevo valor calculado para el punto.
 */
double Caculate_Simulation(Simulation* sim, int64_t row, int64_t col);

#endif  // SIMULATION_HPP