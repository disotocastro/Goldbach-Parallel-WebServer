
#ifndef HTTPDISPATCHER_H
#define HTTPDISPATCHER_H

#include "Dispatcher.hpp"
#include "HttpRequest.hpp"
#include "HttpResponse.hpp"
#include "RequestResponseStruct.hpp"
#include <vector>

class HttpDispatcher : public Dispatcher <std::string, RequestResponseStruct_t>  {
  DISABLE_COPY(HttpDispatcher);

 public:
  explicit HttpDispatcher(); 
  ~HttpDispatcher();

  int run() override;

  void stop();

  std::string extractKey(const RequestResponseStruct_t& data) const override;

  // void consume(RequestResponseStruct_t data) override;

  // void serverNotFound(RequestResponseStruct_t& data) const;

};

#endif  // HTTPDISPATCHER_H
