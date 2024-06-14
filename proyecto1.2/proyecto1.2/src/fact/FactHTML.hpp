// Copyright 2024 Diego Soto, Migueledo Nuñez, William Moraes
// Universidad de Costa Rica. CC BY 4.0

#ifndef FACTHTML_HPP
#define FACTHTML_HPP

#include <string>
#include <vector>

#include "Consumer.hpp"
#include "FactSortAssembler.hpp"
#include "HttpApp.hpp"
#include "Socket.hpp"
#include "numbers.hpp"

class FactHTML : public Consumer<std::vector<FactNumber*>> {
 public:
  /**
   * @brief Método para ejecutar la conexión HTTP.
   * @return Entero que indica el estado de la ejecución.
   */
  int run() override;

  /**
   * @brief Método para consumir un socket.
   * @param client Socket que se va a consumir.
   */
  void consume(std::vector<FactNumber*> data_resolved) override;

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
  void sendSuccessResponse(std::vector<FactNumber*> data_resolved,
                           const std::vector<std::string>& results);
  /**
   * @brief Continuamente consume datos de la cola.
   *
   * Este método consume datos de la cola de manera continua hasta
   * encontrar una condición de detención.
   *
   * @note Asume que la cola de consumo está inicializada.
   */
  void consumeForever() override;

  /**
     * @brief This function takes a list of lists of integers where each inner
     *  list represents a set of factors to be factorized.
     * It calculates the prime factorization for each set of factors and returns
     a vector of strings representing the factorizations.
     *
     * @param generalFactors A vector of vectors of integers representing sets
     of factors to be factorized.
     * @return A vector of strings representing the prime factorizations of the
     i nput sets of factors.
     *
     * The returned factorizations are in the format "p^e * q^f * ...",
     where p, q, etc. are prime factors and e, f, etc. are their corresponding
     exponents.
    */
  std::vector<std::string> FactorizeToString(
      std::vector<FactNumber*> data_resolved);

 protected:
};

#endif  // FACTHTML_HPP
