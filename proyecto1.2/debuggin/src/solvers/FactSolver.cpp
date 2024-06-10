// Copyright 2024 Diego Soto, Migueledo Nuñez, William Morales
// Universidad de Costa Rica. CC BY 4.0

#include "FactSolver.hpp"

std::vector<int64_t> FactSolver::FactorizeVector(int64_t number) {
  std::vector<int64_t> factors;
 
  factors = GetFactors(number);
  
  return factors;
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
