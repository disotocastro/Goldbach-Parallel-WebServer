#include "load_data.hpp"

std::vector<Simulation*> LoadData(std::string file_name) {
  // Crear un objeto ifstream para leer el archivo

  std::ifstream file(file_name);
  if (!file.is_open()) {
    std::cerr << "Error: No se pudo abrir el archivo " << file_name
              << std::endl;
  }

  // Vector para almacenar todas las simulaciones
  std::vector<Simulation*> simulations;

  std::string line;
  while (std::getline(file, line)) {
    Simulation* sim = new Simulation();

    // Crear un objeto istringstream a partir de la línea leída
    std::istringstream iss(line);
    // Extraer los valores de la línea
    iss >> sim->file_name >> sim->delta_time >> sim->thermal_diffusivity >>
        sim->h >> sim->sensitivity;
    // Añadir la simulación al vector

    std::string temp = "./jobs/" + sim->file_name;

    sim->file_name = temp;
    // Llamar
    sim->matrix = read_matrix_from_file(sim->file_name);

    simulations.push_back(sim);
  }
  // Cerrar el archivo
  file.close();

  // //Imprimir los datos leídos
  // for (const auto& sim : simulations) {
  //   std::cout << "Archivo: " << sim.file_name << ", Valor 1: " <<
  //   sim.duration
  //             << ", Valor 2: " << sim.thermal_diffusivity
  //             << ", Valor 3: " << sim.size << ", Valor 4: " <<
  //             sim.sensitivity
  //             << std::endl << std::endl;
  // }

  for (int64_t i = 0; i < simulations[0]->matrix->rows; i++){
    for (int64_t j = 0; j < simulations[0]->matrix->cols; j++)
    {
      std::cout << simulations[0]->matrix->data[i][j]<< ", ";
    }
    std::cout << std::endl;
    
  }
  std::cout << std::endl;
    std::cout << std::endl;
  return simulations;
}

Matrix* read_matrix_from_file(const std::string& file_name) {
  std::ifstream file(file_name, std::ios::binary);
  if (!file.is_open()) {
    std::cerr << "Error: No se pudo abrir el archivo " << file_name
              << std::endl;
    return nullptr;
  }

  int64_t rows = 0;
  int64_t cols = 0;

  // Leer la cantidad de filas
  file.read(reinterpret_cast<char*>(&rows), sizeof(rows));

  // Leer la cantidad de columnas
  file.read(reinterpret_cast<char*>(&cols), sizeof(cols));

  // Crear la matriz bidimensional
  Matrix* matrix = new Matrix(rows, cols);

  // Leer los datos de la matriz
  for (int64_t i = 0; i < matrix->rows; ++i) {
    file.read(reinterpret_cast<char*>(matrix->data[i]),
              matrix->cols * sizeof(double));
  }

  file.close();
  return matrix;
}