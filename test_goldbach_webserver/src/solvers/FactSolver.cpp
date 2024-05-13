#include "FactSolver.hpp"

std::string FactSolver::FactorizeToString(int64_t number) {
    // Obtener los factores del número
    std::vector<int64_t> factors = GetFactors(number);

    // Contar los exponentes de los factores
    std::unordered_map<int64_t, int> exponentCount;
    for (int64_t factor : factors) {
        exponentCount[factor]++;
    }

    // Construir la cadena de factorización
    std::string factorization;
    for (auto index = exponentCount.begin();
             index != exponentCount.end(); ++index) {
        factorization += std::to_string(index->first);
        if (index->second > 1) {
            factorization += "^" + std::to_string(index->second);
        }
        factorization += " * ";
    }
    // Eliminar los últimos caracteres " * " si están presentes
    if (!factorization.empty()) {
        factorization.pop_back();
        factorization.pop_back();
    }

    return factorization;
}

std::vector<std::string> FactSolver::FactorizeVector
        (const std::vector<int64_t>& numbers) {
    std::vector<std::string> factorizations;
    // Factorizar cada número en la lista
    for (int64_t number : numbers) {
        factorizations.push_back(FactorizeToString(number));
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
        }
        else {
          prime++;
        }
    }
    return factors;
}
