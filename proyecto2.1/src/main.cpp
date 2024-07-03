// Copyright [2024] <Diego Soto, William Morales, Migueledo Núñez>

#include <iostream>
#include <string>
#include <thread>

#include "load_data.hpp"
#include "report.hpp"
#include "simulation.hpp"

int main(int argc, char* argv[]) {
  // Verificar si se proporciona el nombre del archivo como argumento
  if (argc < 2) {
    std::cerr << "Error: El nombre del archivo de trabajo es obligatorio."
              << std::endl;
    return EXIT_FAILURE;
  }

  std::string job_file = argv[1];

  // Obtener el número de hilos soportados por el sistema
  // int num_threads = std::thread::hardware_concurrency();
  // Si se proporciona un argumento adicional, utilizarlo como número de hilos
  // if (argc >= 3) {
  //   try {
  //     num_threads = std::stoi(argv[2]);
  //   } catch (const std::invalid_argument& e) {
  //     std::cerr << "Error: El segundo argumento debe ser un número entero."
  //               << std::endl;
  //     return EXIT_FAILURE;
  //   }
  // }
  // Cargar los datos desde el archivo especificado

  std::vector<Simulation*> simulations = LoadData(job_file);

  StartSimulation(simulations);
  Report(simulations);
  return EXIT_SUCCESS;
}
