// Copyright [2024] <Diego Soto, William Morales, Migueledo Núñez>

#include "report.hpp"

#include <regex>

void Report(std::vector<Simulation*> simulations) {
  // Verifica si el vector de simulaciones está vacío.
  if (simulations.empty()) {
    std::cerr << "No hay simulaciones para reportar." << std::endl;
    return;
  }
  // Genera un nuevo nombre de archivo utilizando una función RegexTabName.
  std::string new_file_name = RegexTabName(simulations[0]->file_name);
  // Abre un archivo para escribir los reportes.
  std::ofstream outFile(new_file_name);
  // Si no se puede abrir el archivo, muestra un mensaje de error y termina la
  // función.
  if (!outFile) {
    std::cerr << "Error al abrir el archivo para escritura: " << new_file_name
              << std::endl;
    return;
  }
  // Recorre cada simulación en el vector.
  for (const auto& sim : simulations) {
    // Guarda la matriz en un archivo utilizando una función
    // save_matrix_to_file.
    save_matrix_to_file(sim->matrix, sim->plate_name, sim->k);
    // Formatea el tiempo de la simulación.
    std::string time = format_time(sim->k * sim->delta_time);

    // Escribir los datos en formato TSV
    outFile << sim->plate_name << "\t" << sim->delta_time << "\t"
            << sim->thermal_diffusivity << "\t" << sim->h << "\t"
            << sim->sensitivity << "\t" << sim->k << "\t" << time << std::endl;
  }

  outFile.close();
}

void save_matrix_to_file(const Matrix* matrix,
                         const std::string& original_plate_name, int64_t k) {
  std::string file_name = RegexPlatename(original_plate_name, k);

  std::ofstream file(file_name, std::ios::binary);
  if (!file.is_open()) {
    std::cerr << "Error: No se pudo abrir el archivo " << file_name
              << " para escritura" << std::endl;
    return;
  }

  // Escribir la cantidad de filas
  file.write(reinterpret_cast<const char*>(&matrix->rows),
             sizeof(matrix->rows));

  // Escribir la cantidad de columnas
  file.write(reinterpret_cast<const char*>(&matrix->cols),
             sizeof(matrix->cols));

  // Escribir los datos de la matriz
  for (int64_t i = 0; i < matrix->rows; ++i) {
    file.write(reinterpret_cast<const char*>(matrix->data[i]),
               matrix->cols * sizeof(double));
  }

  file.close();

  if (!file.good()) {
    std::cerr << "Error: Ocurrió un problema al escribir en el archivo "
              << file_name << std::endl;
  }
}

std::string RegexTabName(const std::string& file_name) {
  /**
   * Esta expresión regular retorna el nombre del archivo, sin la extensión.
   * Ejemplo: ./test/jobs/jobXXX.txt
   * Retorna: jobXXX.
   *
   */
  std::string name = "";
  std::regex patron_nombre_archivo(R"(job\d{3}\.)");
  std::smatch coincidencia_nombre;

  if (std::regex_search(file_name, coincidencia_nombre,
                        patron_nombre_archivo)) {
    name = coincidencia_nombre[0].str();
  }
  name += "tsv";

  return name;
}

std::string RegexPlatename(const std::string& original_plate_name, int64_t k) {
  /**
   * Esta expresión regular retorna el nombre de la placa, y le agrega el
   * número K, con un -.
   * Ejemplo: plate001.bin
   * Retorna: plate001-2.bin
   *
   */
  std::regex pattern(R"((plate\d{3})\.bin)");
  std::smatch match;
  std::string file_name;

  if (std::regex_search(original_plate_name, match, pattern)) {
    std::string base_name = match[1].str();
    file_name = base_name + "-" + std::to_string(k) + ".bin";
  } else {
    // Si el nombre no coincide con el patrón esperado, usar el nombre original
    file_name = original_plate_name;
  }

  return file_name;
}

std::string format_time(const time_t seconds) {
  char text[48];  // YYYY/MM/DD hh:mm:ss
  const std::tm& gmt = *std::gmtime(&seconds);
  snprintf(text, sizeof text, "%04d/%02d/%02d\t%02d:%02d:%02d",
           gmt.tm_year - 70, gmt.tm_mon, gmt.tm_mday - 1, gmt.tm_hour,
           gmt.tm_min, gmt.tm_sec);
  return text;
}
