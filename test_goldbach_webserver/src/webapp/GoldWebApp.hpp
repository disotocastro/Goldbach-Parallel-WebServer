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
   * @brief Sends an error response for an invalid request.
   * @param httpResponse The HTTP response object.
  */
  void sendErrorResponse(HttpResponse& httpResponse);



  /**
   * @brief Sends a successful response with Goldbach sums.
   * @param numbersVector A vector containing the numbers to process.
   * @param httpResponse The HTTP response object.
  */
  void sendSuccessResponse(const std::vector<int64_t>& numbersVector, 
                           HttpResponse& httpResponse);
                           
  /**
   * @brief Extracts numbers from the URI of the HTTP request.
   * @param httpRequest The HTTP request object.
   * @param numbersVector A vector to store the extracted numbers.
   * @return true if the numbers were successfully extracted, false otherwise.
   */
  bool getNumbersFromURI(HttpRequest& httpRequest, 
                       std::vector<int64_t>& numbersVector,int longitud, 
                       std::string str);

};

#endif  // GOLDWEBAPP_HPP
