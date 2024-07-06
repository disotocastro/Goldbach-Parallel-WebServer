#include <mpi.h>  // Incluir la cabecera de MPI

#include <chrono>
#include <iostream>
#include <string>
#include <thread>

#include "load_data.hpp"
#include "report.hpp"
#include "simulation.hpp"

int main(int argc, char* argv[]) {
  // Inicializar MPI
  MPI_Init(&argc, &argv);

  int rank, size;
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);
  MPI_Comm_size(MPI_COMM_WORLD, &size);

  // Verificar si se proporciona el nombre del archivo como argumento
  if (argc < 2) {
    if (rank == 0) {
      std::cerr << "Error: El nombre del archivo de trabajo es obligatorio."
                << std::endl;
    }
    MPI_Finalize();
    return EXIT_FAILURE;
  }

  std::string job_file = argv[1];

  // Obtener el número de hilos soportados por el sistema
  int num_threads = std::thread::hardware_concurrency();
  // Si se proporciona un argumento adicional, utilizarlo como número de hilos
  if (argc >= 3) {
    try {
      num_threads = std::stoi(argv[2]);
    } catch (const std::invalid_argument& e) {
      if (rank == 0) {
        std::cerr << "Error: El segundo argumento debe ser un número entero."
                  << std::endl;
      }
      MPI_Finalize();
      return EXIT_FAILURE;
    }
  }

  // Iniciar el cronómetro
  auto start_time = std::chrono::high_resolution_clock::now();

  // Cargar los datos
  std::vector<Simulation*> simulations = LoadData(job_file);

  // Iniciar simulaciones con MPI
  StartSimulation(simulations, num_threads, rank, size);

  if (rank == 0) {
    Report(simulations);
  }

  for (size_t i = 0; i < simulations.size(); i++) {
    if (simulations[i] && simulations[i]->matrix) {
      delete simulations[i]->matrix;  // Elimina el objeto matrix
    }
    delete simulations[i];  // Elimina el objeto simulation
  }

  // Finalizar MPI
  MPI_Finalize();
  // Detener el cronómetro
  auto end_time = std::chrono::high_resolution_clock::now();
  std::chrono::duration<double> elapsed = end_time - start_time;

  // Imprimir el tiempo de ejecución desde el proceso maestro
  if (rank == 0) {
    std::cout << "Tiempo de ejecución: " << elapsed.count() << " segundos."
              << std::endl;
  }
  return EXIT_SUCCESS;
}
