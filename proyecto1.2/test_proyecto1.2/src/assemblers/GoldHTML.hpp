// Copyright 2024 Diego Soto, Migueledo Nuñez, William Moraes
// Universidad de Costa Rica. CC BY 4.0

#ifndef GOLDHTML_HPP
#define GOLDHTML_HPP

#include <vector>

#include "Consumer.hpp"
#include "GoldSortAssembler.hpp"
#include "HttpApp.hpp"
#include "Socket.hpp"
#include "numbers.hpp"

class Gold_HTML : public Consumer<RequestResolved_t*> {
 public:
  explicit Gold_HTML(Queue<RequestResolved_t*>* request_resolved_queue);

  /**
   * @brief Método para ejecutar la conexión HTTP.
   * @return Entero que indica el estado de la ejecución.
   */
  int run() override;

  /**
   * @brief Método para consumir un socket.
   * @param client Socket que se va a consumir.
   */
  void consume(RequestResolved_t* resolved) override;

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
  void sendSuccessResponse(RequestResolved_t* resolved);

  std::vector<std::string> create_strings(RequestResolved_t* numbers);
  
  Queue<RequestResolved_t*>* request_resolved_queue;

 protected:
  /// Puntero a un vector de punteros a objetos HttpApp.
  // Queue<RequestResolved_t*>* request_resolved_queue;
};

#endif  // GOLDHTML_HPP
