// Copyright 2024 Diego Soto, Migueledo Nuñez, William Moraes
// Universidad de Costa Rica. CC BY 4.0

#include "FactSolver.hpp"

std::vector<std::vector<int64_t>> FactSolver::FactorizeVector(
    const std::vector<int64_t>& numbers) {
  std::vector<std::vector<int64_t>> factorizations;

  // Factorizar cada número en la lista
  for (int64_t number : numbers) {
    factorizations.push_back(GetFactors(number));
  }
  return factorizations;
}

std::vector<int64_t> FactSolver::GetFactors(int64_t number) {
  std::vector<int64_t> factors;
  // Si el número es menor que 2, no tiene factores primos
  if (number < 2) {
    return factors;
  }

  // Encontrar los factores primos
  int64_t prime = 2;
  while (number > 1) {
    if (number % prime == 0) {
      factors.push_back(prime);
      number /= prime;
    } else {
      prime++;
    }
  }
  return factors;
}
