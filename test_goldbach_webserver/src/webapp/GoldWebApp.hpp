#ifndef GOLDWEBAPP_HPP
#define GOLDWEBAPP_HPP

#include "HttpApp.hpp"
#include <vector>

/**
 * @brief A web application that calculates Goldbach sums.
 */
class GoldWebApp : public HttpApp {
  DISABLE_COPY(GoldWebApp);

 public:
  /**
   * @brief Constructor.
   */
  GoldWebApp();

  /**
   * @brief Destructor.
   */
  ~GoldWebApp();

  /**
   * @brief Called by the web server when the web server is started.
   */
  void start() override;

  /**
   * @brief Handle HTTP requests.
   * @see HttpServer::handleHttpRequest()
   * @param httpRequest The HTTP request object.
   * @param httpResponse The HTTP response object.
   * @return true If this application handled the request, false otherwise.
   */
  bool handleHttpRequest(HttpRequest& httpRequest,
                         HttpResponse& httpResponse) override;

  /**
   * @brief Called when the web server stops, in order to allow the web application to clean up and finish as well.
   */
  void stop() override;

 protected:
  /**
   * @brief Handle HTTP requests.
   * @param httpRequest The HTTP request object.
   * @param httpResponse The HTTP response object.
   * @return true If this application handled the request, false otherwise.
   * Sends the homepage as HTTP response.
   */
  bool serveHomepage(HttpRequest& httpRequest, HttpResponse& httpResponse);

  /**
   * @brief Handle a HTTP request that starts with "/fact".
   * @param httpRequest The HTTP request object.
   * @param httpResponse The HTTP response object.
   * @return true if the factorization was handled, false if it must be handled by another application.
   */
  bool serveGoldbach(HttpRequest& httpRequest, HttpResponse& httpResponse);

  /**
   * @brief Extracts numbers from the HTTP request URI and fills a vector with them.
   * @param httpRequest The HTTP request object.
   * @return A vector containing the extracted numbers.
   */
  std::vector<int64_t> fillVector(HttpRequest& httpRequest);

  bool sendSuccessResponse(const std::vector<int64_t>& numbersVector, HttpResponse& httpResponse);

  bool sendErrorResponse(HttpResponse& httpResponse);

  std::vector<int64_t> extractNumbers(const std::string& numbersString, bool& hayError);

  std::vector<int64_t> parseHttpRequest(HttpRequest& httpRequest, bool& hayError);
};

#endif  // GOLDWEBAPP_HPP
