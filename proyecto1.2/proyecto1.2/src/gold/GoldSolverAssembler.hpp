// Copyright 2024 Diego Soto, Migueledo Nuñez, William Morales
// Universidad de Costa Rica. CC BY 4.0

#ifndef GOLDSOLVERASSEMBLER_HPP
#define GOLDSOLVERASSEMBLER_HPP

#include "Assembler.hpp"
#include "GoldSolver.hpp"
#include "numbers.hpp"

/**
 * @class GoldSolverAssembler
 * @brief Clase para ensamblar y resolver la conjetura de Goldbach.
 *
 * La clase `GoldSolverAssembler` hereda de `Assembler<Numbers_t*, Numbers_t*>` y proporciona
 * métodos para ejecutar el ensamblador, consumir números y resolver la conjetura de Goldbach.
 */
class GoldSolverAssembler : public Assembler<Numbers_t*, Numbers_t*> {
 public:
  /**
   * @brief Ejecuta el ensamblador.
   *
   * Este método inicia el proceso de consumo y se ejecuta indefinidamente.
   * @return Un entero que representa el estado de salida.
   */
  int run() override;

  /**
   * @brief Consume un número y resuelve la conjetura de Goldbach.
   *
   * Este método recibe un número, resuelve la conjetura de Goldbach para él,
   * y luego produce el resultado.
   * @param number Puntero al número que se va a procesar.
   */
  void consume(Numbers_t* number) override;

  /**
   * @brief Continuamente consume datos de la cola.
   *
   * Este método consume datos de la cola de manera continua hasta
   * encontrar una condición de detención.
   *
   * @note Asume que la cola de consumo está inicializada.
   */
  void consumeForever() override;
};

#endif  // GOLDSOLVERASSEMBLER_HPP
