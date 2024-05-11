#include <iostream>
#include <vector>
#include "FactSolver.hpp" // Incluir el archivo de encabezado de FactSolver

int main() {
    FactSolver factSolver; // Instancia de FactSolver

    // Ejemplo de uso: factorizar un vector de números
    std::vector<int64_t> numbers = {36, 100, 144, 13};
    std::vector<std::string> results = factSolver.FactorizeVector(numbers);

    // Imprimir las factorizaciones
    for (size_t i = 0; i < results.size(); i++) {
        std::cout << "Factorization of " << numbers[i] << ": " << results[i] << std::endl;
    }

    return 0;
}
