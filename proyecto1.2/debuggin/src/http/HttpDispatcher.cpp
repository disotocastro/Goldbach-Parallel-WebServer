#include "HttpDispatcher.hpp"
#include "RequestResponseStruct.hpp"

#include <iostream>
#include <string>

HttpDispatcher::HttpDispatcher() {}

HttpDispatcher::~HttpDispatcher() {}

int HttpDispatcher::run() {
  this->consumeForever();

  // // condicion de parada
  // for (const auto& pair : this->toQueues) {
  //   pair.second->enqueue(this->stopCondition);
  // }

  return EXIT_SUCCESS;
}

// Analizador de URI
std::string HttpDispatcher::extractKey(const RequestResponseStruct_t& data) const {
  std::string uri = data.httpRequest.getURI();
  std::cout << uri << std::endl;
  std::string key = uri.substr(1, 4);
  const auto& itr = this->toQueues.find(key);
  if ( itr == this->toQueues.end() ) {
    key = "fact";
  }
  return key;
}