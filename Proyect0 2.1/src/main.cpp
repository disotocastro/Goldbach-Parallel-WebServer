#include <filesystem>
#include <fstream>
#include <iostream>
#include <string>
#include <thread>
#include <vector>

#include "load_data.hpp"

namespace fs = std::filesystem;

int main(int argc, char* argv[]) {
  if (argc < 2) {
    std::cerr << "Error: El nombre del archivo de trabajo es obligatorio."
              << std::endl;
    return EXIT_FAILURE;
  }

  std::string job_file = argv[1];

  int num_threads = std::thread::hardware_concurrency();

  if (argc >= 3) {
    try {
      num_threads = std::stoi(argv[2]);
    } catch (const std::invalid_argument& e) {
      std::cerr << "Error: El segundo argumento debe ser un número entero."
                << std::endl;
      return EXIT_FAILURE;
    }
  }

  int result = LoadData(job_file);
  
  if (result != 0) {
    std::cerr << "Error: LoadData failed with error code " << result
              << std::endl;
    return EXIT_FAILURE;
  }



  return EXIT_SUCCESS;
}