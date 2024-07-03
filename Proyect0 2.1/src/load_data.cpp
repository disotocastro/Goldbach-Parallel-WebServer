#include "load_data.hpp"

#include <regex>

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
    iss >> sim->plate_name >> sim->delta_time >> sim->thermal_diffusivity >>
        sim->h >> sim->sensitivity;

    // Añadir la simulación al vecto

    /**
      Esta expresion regular retorna la ruta del archivo, menos el jobXXX.txt
      Ejemplo: ./test/jobs/jobXXX.txt
      Retorna: ./test/jobs/
     */
    std::string file_root = "";
    std::regex patron(R"((.+?)job\d+\.txt)");
    std::smatch coincidencia;

    if (std::regex_search(file_name, coincidencia, patron)) {
      file_root = coincidencia[1].str();
    }

    std::string temp = file_root + sim->plate_name;
    sim->plate_name = temp;
    sim->file_name = file_name;

    sim->matrix = read_matrix_from_file(sim->plate_name);

    simulations.push_back(sim);
  }
  file.close();


  for (int64_t i = 0; i < simulations[0]->matrix->rows; i++) {
    for (int64_t j = 0; j < simulations[0]->matrix->cols; j++) {
      std::cout << simulations[0]->matrix->data[i][j] << ", ";
    }
    std::cout << std::endl;
  }
  std::cout << std::endl;
  std::cout << std::endl;
  return simulations;
}

Matrix* read_matrix_from_file(const std::string& plate_name) {
  std::ifstream file(plate_name, std::ios::binary);
  if (!file.is_open()) {
    std::cerr << "Error: No se pudo abrir el archivo " << plate_name
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