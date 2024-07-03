#include "report.hpp"

#include <regex>

void Report(std::vector<Simulation*> simulations) {
  /**
      Esta expresion regular retorna el nombre del archivo, sin la extension.
      Ejemplo: ./test/jobs/jobXXX.txt
      Retorna: jobXXX.
  */

  std::string name = "";
  std::regex patron_nombre_archivo(R"(job\d{3}\.)");
  std::smatch coincidencia_nombre;

  if (std::regex_search(simulations[0]->file_name, coincidencia_nombre,
                        patron_nombre_archivo)) {
    name = coincidencia_nombre[0].str();
  }
  name += "tsv";
  std::cout << name << std::endl;

  std::ofstream outFile(name);
  if (!outFile) {
    std::cerr << "Error al abrir el archivo para escritura: " << name
              << std::endl;
    return;
  }


  for (size_t i = 0; i < simulations.size(); i++) {
    save_matrix_to_file(simulations[i]->matrix, simulations[i]->plate_name, simulations[i]->k);
    std::string time =
        format_time((simulations[i]->k) * (simulations[i]->delta_time));

    // Escribir los datos en formato TSV
    outFile << simulations[i]->plate_name << "\t" << simulations[i]->delta_time
            << "\t" << simulations[i]->thermal_diffusivity << "\t"
            << simulations[i]->h << "\t" << simulations[i]->sensitivity << "\t"
            << simulations[i]->k << "\t" << time << std::endl;
  }


  outFile.close();
}

static std::string format_time(const time_t seconds) {
  // TODO(any): Using C until C++20 std::format() is implemented by compilers
  char text[48];  // YYYY/MM/DD hh:mm:ss
  const std::tm& gmt = *std::gmtime(&seconds);
  snprintf(text, sizeof text, "%04d/%02d/%02d\t%02d:%02d:%02d",
           gmt.tm_year - 70, gmt.tm_mon, gmt.tm_mday - 1, gmt.tm_hour,
           gmt.tm_min, gmt.tm_sec);
  return text;
}

bool save_matrix_to_file(const Matrix* matrix, const std::string& original_plate_name, int64_t k) {
    // Generar el nuevo nombre de archivo
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

    std::ofstream file(file_name, std::ios::binary);
    if (!file.is_open()) {
        std::cerr << "Error: No se pudo abrir el archivo " << file_name << " para escritura" << std::endl;
        return false;
    }

    // Escribir la cantidad de filas
    file.write(reinterpret_cast<const char*>(&matrix->rows), sizeof(matrix->rows));

    // Escribir la cantidad de columnas
    file.write(reinterpret_cast<const char*>(&matrix->cols), sizeof(matrix->cols));

    // Escribir los datos de la matriz
    for (int64_t i = 0; i < matrix->rows; ++i) {
        file.write(reinterpret_cast<const char*>(matrix->data[i]), matrix->cols * sizeof(double));
    }

    file.close();

    if (!file.good()) {
        std::cerr << "Error: Ocurrió un problema al escribir en el archivo " << file_name << std::endl;
        return false;
    }

    return true;
}