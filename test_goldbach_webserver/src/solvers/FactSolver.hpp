#ifndef FACT_SOLVER_HPP
#define FACT_SOLVER_HPP

#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>

class FactSolver {
public:
    std::string FactorizeToString(int64_t number);
    std::vector<std::string> FactorizeVector(const std::vector<int64_t>& numbers);
    std::vector<int64_t> GetFactors(int64_t number);
};

#endif /* FACT_SOLVER_HPP */
