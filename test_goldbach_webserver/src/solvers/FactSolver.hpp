#ifndef FACT_SOLVER_HPP
#define FACT_SOLVER_HPP

#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>

/**
 * @class FactSolver
 * @brief A class for solving factorization problems.
 */
class FactSolver {
public:
    /**
     * @brief Factorize a number into its prime factors 
     * and return the result as a string.
     * @param number The number to factorize.
     * @return A string representing the factorization of the input number.
     */
    std::string FactorizeToString(int64_t number);

    /**
     * @brief Factorize a vector of numbers into their prime factors 
     * and return the results as strings.
     * @param numbers A vector of numbers to factorize.
     * @return A vector of strings representing the factorizations 
     * of the input numbers.
     */
    std::vector<std::string> FactorizeVector
                (const std::vector<int64_t>& numbers);

     /**
     * @brief Get the prime factors of a number.
     * @param number The number to factorize.
     * @return A vector containing the prime factors of the input number.
     */
    std::vector<int64_t> GetFactors(int64_t number);
};

#endif /* FACT_SOLVER_HPP */
