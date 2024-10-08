// Copyright 2024 Diego Soto, Migueledo Nuñez, William Moraes
// Universidad de Costa Rica. CC BY 4.0

#include "HttpDispatcher.hpp"

#include <cassert>
#include <iostream>

HttpDispatcher::HttpDispatcher() {}

HttpDispatcher::~HttpDispatcher() {}

int HttpDispatcher::run() {
  this->consumeForever();

  // condicion de parada
  for (const auto& pair : this->toQueues) {
    RequestResponseStruct_t temp = RequestResponseStruct_t();
    temp.stopCondition = 1;
    pair.second->enqueue(temp);
  }

  return EXIT_SUCCESS;
}

// Analizador de URI
std::string HttpDispatcher::extractKey(
    const RequestResponseStruct_t& data) const {
  std::string uri = data.httpRequest.getURI();
  std::string key = uri.substr(1, 4);

  const auto& itr = this->toQueues.find(key);
  if (itr == this->toQueues.end()) {
    key = "gold";
  }
  return key;
}

void HttpDispatcher::consumeForever() {
  assert(this->consumingQueue);
  int64_t stop = std::thread::hardware_concurrency();
  while (true) {
    // Get the next data to consume, or block while queue is empty
    const RequestResponseStruct_t& data = this->consumingQueue->dequeue();
    // If data is the stop condition, stop the loop
    if (data.stopCondition == 1) {
      stop--;
      if (stop == 0) {
        break;
      }
    } else {
      // Process this data
      this->consume(data);
    }
  }
}
