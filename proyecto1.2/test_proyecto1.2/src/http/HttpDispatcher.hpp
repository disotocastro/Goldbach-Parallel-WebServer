
#ifndef HTTPDISPATCHER_H
#define HTTPDISPATCHER_H

#include "Dispatcher.hpp"
#include "HttpRequest.hpp"
#include "HttpResponse.hpp"
#include "Structs.hpp"
#include <vector>

class HttpDispatcher : public Dispatcher <std::string, reqRes_t>  {
  DISABLE_COPY(HttpDispatcher);

 public:
  explicit HttpDispatcher(); 
  ~HttpDispatcher();

  int run() override;

  void stop();

  std::string extractKey(const reqRes_t& data) const override;

};

#endif  // HTTPDISPATCHER_H
