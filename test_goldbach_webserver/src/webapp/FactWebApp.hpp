// Copyright 2024 Diego Soto, Migueledo Nuñez, William Moraes 
// Universidad de Costa Rica. CC BY 4.0

#ifndef FACTWEBAPP_HPP
#define FACTWEBAPP_HPP

#include "HttpApp.hpp"
#include <vector>
#include <string>

/**
 * @class FactWebApp
 * @brief A web application that calculates prime factors.
 */
class FactWebApp : public HttpApp {
  /// Objects of this class cannot be copied
  DISABLE_COPY(FactWebApp);

 public:
  /// Constructor
  FactWebApp();
  /// Destructor
  ~FactWebApp();
  /// Called by the web server when the web server is started
  void start() override;
  
  /// Handle HTTP requests.
  /// @param httpRequest The HTTP request to handle
  /// @param httpResponse The HTTP response to fill
  /// @return true If this application handled the request, false otherwise
  /// and another chained application should handle it
  bool handleHttpRequest(HttpRequest& httpRequest,
    HttpResponse& httpResponse) override;

  /// Called when the web server stops, in order to allow the web application
  /// clean up and finish as well
  void stop() override;

 protected:
  /// Handle HTTP requests.
  /// @param httpRequest The HTTP request to handle
  /// @param httpResponse The HTTP response to fill
  /// @return true If this application handled the request, false otherwise
  /// Sends the homepage as HTTP response
  bool serveHomepage(HttpRequest& httpRequest, HttpResponse& httpResponse);

  /// Handle a HTTP request that starts with "/fact".
  /// @param httpRequest The HTTP request to handle
  /// @param httpResponse The HTTP response to fill
  /// @return true if the factorization was handled, false if it must be
  /// handled by another application
  bool serveFactorization(HttpRequest& httpRequest, HttpResponse& httpResponse);

  /**
   * @brief Get the prime factorization results for a vector of numbers.
   * @param numbersVector The vector of numbers to factorize
   * @return A vector of strings with the factorization results
   */
  std::vector<std::vector<int64_t>> getResults
    (std::vector<int64_t> numbersVector);

  /**
   * @brief Fill a vector of integers from a string representation.
   * @param numbersString The string containing numbers separated by spaces.
   * @return A vector of integers.
   */
  std::vector<int64_t> fillVector(std::string numbersString);

  /**
   * @brief Sends an error HTTP response.
   * 
   * This method is responsible for generating and sending an HTTP response 
   * indicating an error occurred during processing of a request.
   * 
   * @param httpResponse The HTTP response object to fill with 
   *  the error response.
   */
  void sendErrorResponse(HttpResponse& httpResponse);

  /**
   * @brief Sends a successful HTTP response with factorization results.
   * 
   * This method is responsible for generating and sending an HTTP response 
   * containing the factorization results for a successful request.
   * 
   * @param httpResponse The HTTP response object to fill with the successful
   * response.
   * @param numbersVector The vector of numbers that were factorized.
   * @param results The vector of strings containing the factorization results.
   */
  void sendSuccessResponse(HttpResponse& httpResponse, 
                                     const std::vector<int64_t>& numbersVector, 
                                     const std::vector<std::string>& results);
                                                                
  /**
   * @brief This function takes a list of lists of integers where each inner list 
   represents a set of factors to be factorized.
   * It calculates the prime factorization for each set of factors and returns 
   a vector of strings representing the factorizations.
   * 
   * @param generalFactors A vector of vectors of integers representing sets of 
   factors to be factorized.
   * @return A vector of strings representing the prime factorizations of the i
   nput sets of factors.
   * 
   * The returned factorizations are in the format "p^e * q^f * ...", 
   where p, q, etc. are prime factors and e, f, etc. are their corresponding 
   exponents.
  */
  std::vector<std::string> FactorizeToString 
                                            (std::vector<std::vector<int64_t>>);

};

#endif  // FACTWEBAPP_HPP
