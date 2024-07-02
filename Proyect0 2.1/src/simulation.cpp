#include "load_data.hpp"
#include "matrix.hpp"
#include "simulation.hpp"

void Start_Simulations(std::vector<Simulation*> simulations) {
  for (size_t i = 0; i < simulations.size(); ++i) {
    Run_Simulation(simulations[i]);
  }
}

void Run_Simulation(Simulation* sim) {
  double sensitivity = sim->sensitivity;  // e
  double C = 0;
  int64_t k = 0;

  double** temp = new double*[sim->matrix->rows];
  for (int64_t i = 0; i < sim->matrix->rows; ++i) {
    temp[i] = new double[sim->matrix->cols];
    for (int64_t j = 0; j < sim->matrix->cols; ++j) {
      temp[i][j] = sim->matrix->data[i][j];  // Copiar cada elemento
    }
  }

  do {
    for (int64_t i = 1; i < sim->matrix->rows - 1; i++) {
      for (int64_t j = 1; j < sim->matrix->cols - 1; j++) {
        // temp[i][j] =
        //     Caculate_Simulation(sim, sim->matrix->rows, sim->matrix->cols);
      }
    }
    sim->matrix->data = temp;
    k++;
  } while (C > sensitivity);
}

double Caculate_Simulation(Simulation* sim, int64_t row, int64_t col) {
  // std::abs()
  double delta_time = sim->delta_time;
  double thermal_diffusivity = sim->thermal_diffusivity;  // cita
  double h = sim->h;

  double** tmatrix = sim->matrix->data;

  double energy_loss = ((tmatrix[row][col]) * (-4));

  double transfer = ((delta_time * thermal_diffusivity) / (h * h));

  double neighbors = ((tmatrix[row - 1][col]) + (tmatrix[row + 1][col]) +
                      (tmatrix[row][col - 1]) + (tmatrix[row][col + 1]));

  return (tmatrix[row][col]) + (transfer * (neighbors - energy_loss));
}