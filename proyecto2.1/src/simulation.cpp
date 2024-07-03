// Copyright [2024] <Diego Soto, William Morales, Migueledo Núñez>

#include "simulation.hpp"

#include "load_data.hpp"
#include "matrix.hpp"
#include "report.hpp"

void StartSimulation(std::vector<Simulation*> simulations) {
  for (size_t i = 0; i < simulations.size(); ++i) {
    RunSimulation(simulations[i]);
  }
}

void RunSimulation(Simulation* sim) {
  double sensitivity = sim->sensitivity;  // e
  double C;
  sim->k = 0;

  double** temp = new double*[sim->matrix->rows];

  for (int64_t i = 0; i < sim->matrix->rows; ++i) {
    temp[i] = new double[sim->matrix->cols];
    for (int64_t j = 0; j < sim->matrix->cols; ++j) {
      temp[i][j] = sim->matrix->data[i][j];  // Copiar cada elemento
    }
  }

  do {
    C = 0.0;
    for (int64_t i = 1; i < sim->matrix->rows - 1; i++) {
      for (int64_t j = 1; j < sim->matrix->cols - 1; j++) {
        temp[i][j] = CaculateSimulation(sim, i, j);
        double diff = std::abs((sim->matrix->data[i][j]) - (temp[i][j]));
        if (diff > C) {
          C = diff;
        }
      }
    }

    for (int64_t i = 0; i < sim->matrix->rows; ++i) {
      for (int64_t j = 0; j < sim->matrix->cols; ++j) {
        sim->matrix->data[i][j] = temp[i][j];  // Copiar cada elemento
      }
    }

    sim->k++;
  } while (C > sensitivity);
}

double CaculateSimulation(Simulation* sim, int64_t row, int64_t col) {
  double delta_time = sim->delta_time;
  double thermal_diffusivity = sim->thermal_diffusivity;
  double h = sim->h;

  double** tmatrix = sim->matrix->data;

  double transfer = (delta_time * thermal_diffusivity) / (h * h);

  double neighbors = (tmatrix[row - 1][col] + tmatrix[row + 1][col] +
                      tmatrix[row][col - 1] + tmatrix[row][col + 1]);

  return tmatrix[row][col] + transfer * (neighbors - 4 * tmatrix[row][col]);
}
