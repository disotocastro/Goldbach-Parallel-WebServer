// Copyright 2024 Diego Soto, Migueledo Nuñez, William Morales
// Universidad de Costa Rica. CC BY 4.0

#ifndef FACTWEBAPP_HPP
#define FACTWEBAPP_HPP

#include <queue>
#include <vector>

#include "FactHTML.hpp"
#include "FactSolverAssembler.hpp"
#include "FactSortAssembler.hpp"
#include "FactUriAnalizer.hpp"
#include "HttpApp.hpp"

/**
 * @class FactWebApp
 * @brief A web application that calculates prime factors.
 *
 * This class represents a web application responsible for calculating prime
 * factors of numbers provided via HTTP requests.
 */
class FactWebApp : public HttpApp {
  /// Objects of this class cannot be copied
  DISABLE_COPY(FactWebApp);

 public:
  /// MAX NUMBER OF CONNECTIONS
  int64_t maxSolvers = std::thread::hardware_concurrency();

  /**
   * @brief Vector de punteros a objetos FactSolverAssembler.
   */
  std::vector<FactSolverAssembler*> vectorSolverAssemblers;

  /**
   * @brief Analyzer for URIs to extract FactNumber objects.
   */
  FactUriAnalizer* uriAnalizer;
  /**
   * @brief Assembler for sorting FactNumber objects.
   */
  FactSortAssembler* sortAssembler;
  /**
   * @brief Object for building HTML responses.
   */
  FactHTML* buildHTML;

  /// Constructor
  FactWebApp();

  /// Destructor
  ~FactWebApp();

  /**
   * @brief Llamado por el servidor web cuando el servidor web es iniciado.
   */
  void start() override;

  /**
   * @brief Llamado cuando el servidor web se detiene, para permitir que la
   * aplicación web también se limpie y termine.
   */
  void stop() override;
};
#endif  // FACTWEBAPP_HPP
