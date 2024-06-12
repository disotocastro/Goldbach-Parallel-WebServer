// Copyright 2024 Diego Soto, Migueledo Nuñez, William Morales
// Universidad de Costa Rica. CC BY 4.0

#ifndef FACTSOLVERASSEMBLER_HPP
#define FACTSOLVERASSEMBLER_HPP

#include <string>
#include <vector>

#include "Assembler.hpp"
#include "FactNumber.hpp"
#include "FactSolver.hpp"
#include "HttpApp.hpp"
#include "HttpRequest.hpp"
#include "HttpResponse.hpp"
#include "Queue.hpp"
#include "RequestResponseStruct.hpp"
#include "Socket.hpp"

/**
 * @class FactSolverAssembler
 * @brief Clase encargada de factorizar números y enviar la respuesta
 * correspondiente.
 *
 * Esta clase hereda de Assembler y se encarga de procesar objetos FactNumber.
 * La clase factoriza el número contenido en FactNumber usando FactSolver y
 * luego produce el resultado para ser enviado como respuesta.
 */
class FactSolverAssembler : public Assembler<FactNumber*, FactNumber*> {
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

  /**
   * @brief Consume un objeto FactNumber y lo factoriza.
   *
   * Este método recibe un puntero a un objeto FactNumber, lo factoriza
   * utilizando FactSolver y luego produce el objeto resultante.
   *
   * @param data Puntero al objeto FactNumber que se va a consumir.
   */
  void consume(FactNumber* data) override;
};

#endif  // FACTSOLVERASSEMBLER_HP
