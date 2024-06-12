// Copyright 2024 Diego Soto, Migueledo Nuñez, William Morales
// Universidad de Costa Rica. CC BY 4.0

#ifndef GOLDSOLVERASSEMBLER_HPP
#define GOLDSOLVERASSEMBLER_HPP

#include <string>
#include <vector>
#include <map>
#include <iostream>

#include "Assembler.hpp"
#include "GoldSolver.hpp"
#include "HttpRequest.hpp"
#include "HttpResponse.hpp"
#include "numbers.hpp"

/**
 * @class FactSolverAssembler
 * @brief Clase encargada de factorizar números y enviar la respuesta
 * correspondiente.
 *
 * Esta clase hereda de Assembler, se encarga de procesar estructuras Numbers_t.
 * La clase se encarga de realizar las sumas de goldbach con el número de Numbers_t 
 * luego produce el resultado para ser enviado como respuesta.
 */
class GoldSolverAssembler : public Assembler<Numbers_t*, Numbers_t*> {
 public:
  /**
   * @brief Ejecuta el proceso de conexión HTTP.
   *
   * Este método inicia el ciclo de consumo continuo de solicitudes y
   * responde con la factorización de los números recibidos.
   *
   * @return Estado de la ejecución (EXIT_SUCCESS).
   */
  int run() override;

  void consume(Numbers_t* number) override;
};

#endif  // GOLDSOLVERASSEMBLER_HPP
