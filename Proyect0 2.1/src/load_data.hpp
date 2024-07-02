#ifndef LOAD_DATA_HPP
#define LOAD_DATA_HPP

#include <string>
#include "matrix.hpp"

// Define the Simulation struct
struct Simulation {
  Matrix* matrix;
  std::string file_name;
  double duration;
  double thermal_diffusivity;
  double size;
  double sensitivity;
};


int LoadData(std::string file_name);

Matrix* read_matrix_from_file(const std::string& file_name);



#endif  // LOAD_DATA_HPP