// Copyright 2024 Diego Soto, Migueledo Nuñez, William Moraes
// Universidad de Costa Rica. CC BY 4.0
#ifndef GOLDWEBAPP_HPP
#define GOLDWEBAPP_HPP

#include <string>
#include <vector>

#include "GoldAnalizaURI.hpp"
#include "GoldSolverAssambler.hpp"
#include "HttpApp.hpp"
#include "numbers.hpp"

/**
 * @brief A web application that calculates Goldbach sums.
 */
class GoldWebApp : public HttpApp {
  DISABLE_COPY(GoldWebApp);

 public:
  /**
   * @brief Constructor.
   */
  GoldWebApp();

  /**
   * @brief Destructor.
   */
  ~GoldWebApp();

  /**
   * @brief Called by the web server when the web server is started.
   */
  void start() override;

  /**
   * @brief Handle HTTP requests.
   * @see HttpServer::handleHttpRequest()
   * @param httpRequest The HTTP request object.
   * @param httpResponse The HTTP response object.
   * @return true If this application handled the request, false otherwise.
   */
  bool handleHttpRequest(HttpRequest& httpRequest,
                         HttpResponse& httpResponse) override;

  /**
   * @brief Called when the web server stops, in order to allow the web
   * application to clean up and finish as well.
   */
  void stop() override;

 protected:
  /**
   * @brief Handle HTTP requests.
   * @param httpRequest The HTTP request object.
   * @param httpResponse The HTTP response object.
   * @return true If this application handled the request, false otherwise.
   * Sends the homepage as HTTP response.
   */
  bool serveHomepage(HttpRequest& httpRequest, HttpResponse& httpResponse);

  /**
   * @brief Handle a HTTP request that starts with "/fact".
   * @param httpRequest The HTTP request object.
   * @param httpResponse The HTTP response object.
   * @return true if the factorization was handled, false if it must be handled
   * by another application.
   */
  bool serveGoldbach(HttpRequest& httpRequest, HttpResponse& httpResponse);

  /**
   * @brief Sends an error response for an invalid request.
   * @param httpResponse The HTTP response object.
   */
  void sendErrorResponse(HttpResponse& httpResponse);

  /**
   * @brief Sends a successful response with Goldbach sums.
   * @param numbersVector A vector containing the numbers to process.
   * @param httpResponse The HTTP response object.
   */
  void sendSuccessResponse(const std::vector<int64_t>& numbersVector,
                           HttpResponse& httpResponse);

  /**
   * @brief Crea cadenas de texto representando las sumas de Goldbach.
   */
  std::vector<std::string> create_strings(NumbersArray_t* numbers);

  std::string id;
  Queue<RequestResponseStruct>* requestResponseQueue;
  Queue<Numbers_t*>* numbersQueue;
  URI_Analyzer* uriAnalyzer;
  Solver_Assembler* solverAsembler;
  Queue<Numbers_t*>* numbers_t_queue_resolved;
};

#endif  // GOLDWEBAPP_HPP
