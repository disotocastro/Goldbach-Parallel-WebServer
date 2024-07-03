#include "report.hpp"

#include <regex>

void Report(Simulation* sim) {
  /**
      Esta expresion regular retorna el nombre del archivo, sin la extension.
      Ejemplo: ./test/jobs/jobXXX.txt
      Retorna: jobXXX.
  */

  std::string name = "";
  std::regex patron_nombre_archivo(R"(job\d{3}\.)");
  std::smatch coincidencia_nombre;

  if (std::regex_search(sim->file_name, coincidencia_nombre,
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

  std::string time = format_time((sim->k) * (sim->delta_time));

  // Escribir los datos en formato TSV
  outFile << sim->plate_name << "\t" << sim->delta_time << "\t"
          << sim->thermal_diffusivity << "\t" << sim->h << "\t"
          << sim->sensitivity << "\t" << sim->k << "\t" << time << std::endl;

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
