#ifndef SIMULATION_HPP
#define SIMULATION_HPP

#include <load_data.hpp>
#include <matrix.hpp>

void Start_Simulations(std::vector<Simulation*> simulations);

void Run_Simulation(Simulation* sim);

double Caculate_Simulation(Simulation& sim, int64_t row, int64_t col);
#endif  // SIMULATION_HPP
