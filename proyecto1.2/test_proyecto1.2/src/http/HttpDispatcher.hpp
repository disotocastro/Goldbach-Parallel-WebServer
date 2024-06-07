
#ifndef HTTPDISPATCHER_H
#define HTTPDISPATCHER_H

#include "Dispatcher.hpp"
#include "HttpRequest.hpp"
#include "HttpResponse.hpp"
#include "RequestResponseQueue.hpp"
#include <vector>

class HttpDispatcher : public Dispatcher <std::string, RequestResponseQueue>  {
  DISABLE_COPY(HttpDispatcher);

 public:
  explicit HttpDispatcher(); 
  ~HttpDispatcher();

  int run() override;

  void stop();

  std::string extractKey(const RequestResponseQueue& data) const override;

};

#endif  // HTTPDISPATCHER_H
