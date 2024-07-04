// Copyright [2024] <Diego Soto, William Morales, Migueledo Núñez>

#include "simulation.hpp"


void StartSimulation(std::vector<Simulation*> simulations, int num_threads) {
// Inicia la simulación para cada objeto Simulation en el vector.
#pragma omp parallel for num_threads(num_threads) \
    schedule(dynamic) default(none) shared(simulations, std::cout)
  for (size_t i = 0; i < simulations.size(); ++i) {
    std::cout << omp_get_thread_num() << std::endl;
    RunSimulation(simulations[i]);
  }
}

void RunSimulation(Simulation* sim) {
  double sensitivity = sim->sensitivity;  // e
  double C;
  sim->k = 0;
  // Crear una copia temporal de la matriz de datos
  double** temp = new double*[sim->matrix->rows];
  for (int64_t i = 0; i < sim->matrix->rows; ++i) {
    temp[i] = new double[sim->matrix->cols];
    for (int64_t j = 0; j < sim->matrix->cols; ++j) {
      temp[i][j] = sim->matrix->data[i][j];  // Copiar cada elemento
    }
  }
  // Bucle principal de la simulación
  do {
    C = 0.0;  // Reiniciar la diferencia máxima para la iteración actual
    for (int64_t i = 1; i < sim->matrix->rows - 1; i++) {
      for (int64_t j = 1; j < sim->matrix->cols - 1; j++) {
        temp[i][j] = CaculateSimulation(sim, i, j);  // Calcular el nuevo valor
        double diff = std::abs((sim->matrix->data[i][j]) - (temp[i][j]));
        if (diff > C) {
          C = diff;  // Actualizar la diferencia máxima
        }
      }
    }
    // Copiar los nuevos valores a la matriz original
    for (int64_t i = 0; i < sim->matrix->rows; ++i) {
      for (int64_t j = 0; j < sim->matrix->cols; ++j) {
        sim->matrix->data[i][j] = temp[i][j];  // Copiar cada elemento
      }
    }

    sim->k++;  // Incrementar el contador de iteraciones
  } while (C > sensitivity);

  for (int64_t i = 0; i < sim->matrix->rows; ++i) {
    delete[] temp[i];
  }
  delete[] temp;
}

double CaculateSimulation(Simulation* sim, int64_t row, int64_t col) {
  double delta_time = sim->delta_time;                    // Intervalo de tiempo
  double thermal_diffusivity = sim->thermal_diffusivity;  // Difusividad térmica
  double h = sim->h;                                      // Tamaño de paso
  // Matriz de datos
  double** tmatrix = sim->matrix->data;
  // Coeficiente de transferencia de calor
  double transfer = (delta_time * thermal_diffusivity) / (h * h);
  // Suma de los valores de las celdas vecinas
  double neighbors = (tmatrix[row - 1][col] + tmatrix[row + 1][col] +
                      tmatrix[row][col - 1] + tmatrix[row][col + 1]);
  // Calcular y devolver el nuevo valor de la celda
  return tmatrix[row][col] + transfer * (neighbors - 4 * tmatrix[row][col]);
}
