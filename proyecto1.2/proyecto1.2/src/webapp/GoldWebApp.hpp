
// Copyright 2024 Diego Soto, Migueledo Nuñez, William Moraes
// Universidad de Costa Rica. CC BY 4.0
#ifndef GOLDWEBAPP_HPP
#define GOLDWEBAPP_HPP

#include <vector>

#include "GoldHTML.hpp"
#include "GoldSolverAssembler.hpp"
#include "GoldSortAssembler.hpp"
#include "GoldUriAnalizer.hpp"
#include "HttpApp.hpp"

/**
 * @brief A web application that calculates Goldbach sums.
 */
class GoldWebApp : public HttpApp {
  DISABLE_COPY(GoldWebApp);

 public:
  /**
   * @brief Número máximo de ensambladores de solucionadores.
   */
  int64_t maxSolvers = std::thread::hardware_concurrency();
  /**
   * @brief Vector de ensambladores de solucionadores.
   */
  std::vector<GoldSolverAssembler*> vectorSolverAssemblers;
  /**
   * @brief Analizador de URI.
   */
  GoldUriAnalizer* uriAnalizer;
  /**
   * @brief Ensamblador de ordenamiento.
   */
  GoldSortAssembler* sortAssembler;
  /**
   * @brief Constructor.
   */
  GoldHTML* buildHTML;

  /**
   * @brief Constructor.
   */
  GoldWebApp();

  /**
  GoldUriAnalizer* uriAnalizer;
   * @brief Destructor.
   */
  ~GoldWebApp();

  /**
   * @brief Called by the web server when the web server is started.
   */
  void start() override;

  /**
   * @brief Called when the web server stops, in order to allow the web
   * application to clean up and finish as well.
   */
  void stop() override;
};

#endif  // GOLDWEBAPP_HPP
