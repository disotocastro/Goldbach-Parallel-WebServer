// Copyright 2024 Diego Soto, Migueledo Nuñez, William Morales
// Universidad de Costa Rica. CC BY 4.0

#ifndef FACTWEBAPP_HPP
#define FACTWEBAPP_HPP

#include <string>
#include <vector>

#include "HttpApp.hpp"
#include "FactUriAnalizer.hpp"
#include "FactSortAssembler.hpp"
#include "FactSolverAssembler.hpp"
#include "FactNumber.hpp"
#include "Queue.hpp"
#include "FactHTML.hpp"

/**
 * @class FactWebApp
 * @brief A web application that calculates prime factors.
 */
class FactWebApp : public HttpApp {
  /// Objects of this class cannot be copied
  DISABLE_COPY(FactWebApp);

 public:
  Queue<FactNumber*>* FactNumberQueue;
  Queue<FactNumber*>* FactNumberSolvedQueue;
  FactSolverAssembler* solverAssembler;
  FactUriAnalizer* uriAnalizer;
  FactSortAssembler* sortAssembler;
  FactHTML* buildHTML;

  /// Constructor
  FactWebApp();

  /// Destructor
  ~FactWebApp();

  /// Called by the web server when the web server is started
  void start() override;
  
  /// Called when the web server stops, in order to allow the web application
  /// clean up and finish as well
  void stop() override;

};
#endif  // FACTWEBAPP_HPP

