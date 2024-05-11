#include "FactSolver.hpp"

std::string FactSolver::FactorizeToString(int64_t number) {
    std::vector<int64_t> factors = GetFactors(number);
    std::unordered_map<int64_t, int> exponentCount;
    for (int64_t factor : factors) {
        exponentCount[factor]++;
    }

    std::string factorization;
    for (auto index = exponentCount.begin(); index != exponentCount.end(); ++index) {
        factorization += std::to_string(index->first);
        if (index->second > 1) {
            factorization += "^" + std::to_string(index->second);
        }
        factorization += " * ";
    }
    if (!factorization.empty()) {
        factorization.pop_back();
        factorization.pop_back();
    }

    return factorization;
}

std::vector<std::string> FactSolver::FactorizeVector(const std::vector<int64_t>& numbers) {
    std::vector<std::string> factorizations;
    for (int64_t number : numbers) {
        factorizations.push_back(FactorizeToString(number));
    }
    return factorizations;
}

std::vector<int64_t> FactSolver::GetFactors(int64_t number) {
    std::vector<int64_t> factors;
    if (number < 2) {
        return factors;
    }

    int64_t prime = 2;
    while (number > 1) {
        if (number % prime == 0) {
          factors.push_back(prime);
          number /= prime;
        }
        else {
          prime++;
        }
    }
    return factors;
}



// #include <iostream>
// #include <vector>
// #include "FactSolver.hpp" // Incluir el archivo de encabezado de FactSolver

// int main() {
//     FactSolver factSolver; // Instancia de FactSolver

//     // Ejemplo de uso: factorizar un vector de números
//     std::vector<int64_t> numbers = {36, 100, 144, 13};
//     std::vector<std::string> results = factSolver.FactorizeVector(numbers);

//     // Imprimir las factorizaciones
//     for (size_t i = 0; i < results.size(); i++) {
//         std::cout << "Factorization of " << numbers[i] << ": " << results[i] << std::endl;
//     }

//     return 0;
// }
