#include "HttpDispatcher.hpp"

HttpDispatcher::HttpDispatcher() {}

HttpDispatcher::~HttpDispatcher() {
}

int HttpDispatcher::run() {
  this->consumeForever();

  // condicion de parada
  for ( const auto& pair : this->toQueues ) {
    pair.second->enqueue(this->stopCondition);
  }

  return EXIT_SUCCESS;
}

std::string HttpDispatcher::extractKey(const RequestResponseStruct& data) const{
  std::string uri = data.httpRequest->getURI();
  return uri;
}

void HttpDispatcher::stop() { }
