// Copyright 2024 Diego Soto, Migueledo Nuñez, William Morales
// Universidad de Costa Rica. CC BY 4.0

#ifndef FACT_SOLVER_HPP
#define FACT_SOLVER_HPP

#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>

/**
 * @class FactSolver
 * @brief A class for solving factorization problems.
 */
class FactSolver {
 public:
  /**
   * @brief Factorize a vector of numbers into their prime factors
   * and return the results as strings.
   * @param numbers A vector of numbers to factorize.
   * @return A vector of strings representing the factorizations
   * of the input numbers.
   */
  std::vector<int64_t> FactorizeVector(int64_t numbers);

  /**
   * @brief Get the prime factors of a number.
   * @param number The number to factorize.
   * @return A vector containing the prime factors of the input number.
   */
  std::vector<int64_t> GetFactors(int64_t number);
};

#endif /* FACT_SOLVER_HPP */
