// Copyright 2024 Diego Soto, Migueledo Nuñez, William Moraes
// Universidad de Costa Rica. CC BY 4.0

#ifndef HTTPDISPATCHER_H
#define HTTPDISPATCHER_H

#include <string>
#include <vector>

#include "Dispatcher.hpp"
#include "RequestResponseStruct.hpp"

/**
 * @class HttpDispatcher
 * @brief A class for handling HTTP dispatching.
 *
 * This class inherits from the Dispatcher class and is responsible for
 * dispatching HTTP requests based on extracted keys from URIs.
 */
class HttpDispatcher : public Dispatcher<std::string, RequestResponseStruct_t> {
  DISABLE_COPY(HttpDispatcher);

 public:
  /**
   * @brief Constructor for HttpDispatcher.
   *
   * Initializes a new instance of the HttpDispatcher class.
   */
  HttpDispatcher();
  /**
   * @brief Destructor for HttpDispatcher.
   */
  ~HttpDispatcher();
  /**
   * @brief Runs the HTTP dispatcher.
   *
   * Starts consuming requests and dispatches them indefinitely.
   *
   * @return An integer indicating the success of the operation.
   */
  int run() override;
  /**
   * @brief Stops the HTTP dispatcher.
   *
   * This function stops the dispatcher from processing further requests.
   */
  void stop();
  /**
   * @brief Extracts the key from the HTTP request.
   *
   * This function extracts a key from the given RequestResponseStruct_t object,
   * which is used for dispatching the request to the appropriate handler.
   *
   * @param data The RequestResponseStruct_t object containing the HTTP request.
   * @return A string representing the extracted key.
   */
  std::string extractKey(const RequestResponseStruct_t& data) const override;
  
  bool serveHomepage(RequestResponseStruct_t data);
};

#endif  // HTTPDISPATCHER_H
