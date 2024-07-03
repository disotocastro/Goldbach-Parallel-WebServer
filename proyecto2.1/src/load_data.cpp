// Copyright [2024] <Diego Soto, William Morales, Migueledo Núñez>

#include "load_data.hpp"

std::vector<Simulation*> LoadData(std::string file_name) {
  std::ifstream file(file_name);
  if (!file.is_open()) {
    // Si no se puede abrir el archivo, muestra un mensaje de error y termina la
    // función.
    std::cerr << "Error: No se pudo abrir el archivo " << file_name
              << std::endl;
  }
  // Vector que almacenará punteros a objetos Simulation.
  std::vector<Simulation*> simulations;

  std::string line;
  // Lee el archivo línea por línea.
  while (std::getline(file, line)) {
    // Crea un nuevo objeto Simulation dinámicamente.
    Simulation* sim = new Simulation();
    // Utiliza un string stream para extraer los valores de la línea.
    std::istringstream iss(line);
    iss >> sim->plate_name >> sim->delta_time >> sim->thermal_diffusivity >>
        sim->h >> sim->sensitivity;
    // Obtiene la raíz del nombre del archivo usando una función RegexFileRoot.
    std::string file_root = RegexFileRoot(file_name);
    // Construye el nombre del archivo para leer la matriz de datos.
    std::string temp = file_root + sim->plate_name;
    sim->file_name = file_name;
    // Lee la matriz de datos desde el archivo construido.
    sim->matrix = read_matrix_from_file(temp);
    // Agrega el objeto Simulation al vector.
    simulations.push_back(sim);
  }
  file.close();
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

std::string RegexFileRoot(const std::string& file_name) {
  /**
   * Esta expresión regular retorna la ruta del archivo, menos el jobXXX.txt
   * Ejemplo: ./test/jobs/jobXXX.txt
   * Retorna: ./test/jobs/
   */
  std::string file_root = "";
  std::regex patron(R"((.+?)job\d+\.txt)");
  std::smatch coincidencia;

  if (std::regex_search(file_name, coincidencia, patron)) {
    file_root = coincidencia[1].str();
  }

  return file_root;
}
