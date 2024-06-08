// Copyright 2024 Diego Soto, Migueledo Nuñez, William Moraes
// Universidad de Costa Rica. CC BY 4.0

#include "HttpConnectionHandler.hpp"

#include <string>
#include <vector>

#include "HttpApp.hpp"
#include "HttpRequest.hpp"
#include "HttpResponse.hpp"
#include "Log.hpp"
#include "NetworkAddress.hpp"

HttpConnectionHandler::HttpConnectionHandler(std::vector<HttpApp*>* WebApps) {
  this->applications = WebApps;
}

int HttpConnectionHandler::run() {
  this->consumeForever();
  return EXIT_SUCCESS;
}

void HttpConnectionHandler::consume(Socket client) {
  /// While the same client asks for HTTP requests in the same connection
  while (true) {
    /// Create an object that parses the HTTP request from the socket
    HttpRequest httpRequest(client);

    /// If the request is not valid or an error happened
    if (!httpRequest.parse()) {
      /// Non-valid requests are normal after a previous valid request. Do not
      /// close the connection yet, because the valid request may take time to
      /// be processed. Just stop waiting for more requests
      break;
    }

    /// A complete HTTP client request was received. Create an object for the
    /// server responds to that client's request
    HttpResponse httpResponse(client);

    /// Give subclass a chance to respond the HTTP request
    const bool handled = this->handleHttpRequest(httpRequest, httpResponse);

    /// If subclass did not handle the request or the client used HTTP/1.0
    if (!handled || httpRequest.getHttpVersion() == "HTTP/1.0") {
      /// The socket will not be more used, close the connection
      client.close();
      break;
    }
  }
}

bool HttpConnectionHandler::handleHttpRequest(HttpRequest& httpRequest,
                                              HttpResponse& httpResponse) {
  /// Print IP and port from client
  const NetworkAddress& address = httpRequest.getNetworkAddress();
  Log::append(Log::INFO, "connection",
              std::string("connection established with client ") +
                  address.getIP() + " port " +
                  std::to_string(address.getPort()));

  /// Print HTTP request
  Log::append(Log::INFO, "request",
              httpRequest.getMethod() + ' ' + httpRequest.getURI() + ' ' +
                  httpRequest.getHttpVersion());

  return this->route(httpRequest, httpResponse);
}

// bool HttpConnectionHandler::route(HttpRequest& httpRequest,
//                                   HttpResponse& httpResponse) {
//   /// Traverse the chain of applications
//   for (size_t index = 0; index < (*(this->applications)).size(); ++index) {
//     /// If this application handles the request
//     HttpApp* app = (*(this->applications))[index];
//     if (app->handleHttpRequest(httpRequest, httpResponse)) {
//       return true;
//     }
//   }

//   /// Unrecognized request
//   return this->serveNotFound(httpRequest, httpResponse);
// }

bool HttpConnectionHandler::route(HttpRequest& httpRequest,
                                  HttpResponse& httpResponse) {
  // Instancia del struct
  RequestResponseStruct reqRes(&httpRequest, &httpResponse, 0);
  // Traverse the chain of applications
  for (size_t index = 0; index < (*(this->applications)).size(); ++index) {
    // If this application handles the request
    HttpApp* app = (*(this->applications))[index];
    if (app->handleHttpRequest(httpRequest, httpResponse)) {
      // Darle un ID a cada request
      reqRes.id = index + 1;
      produce(reqRes);
      return true;
    }
  }
  // Unrecognized request
  return this->serveNotFound(httpRequest, httpResponse);
}

bool HttpConnectionHandler::serveNotFound(HttpRequest& httpRequest,
                                          HttpResponse& httpResponse) {
  (void)httpRequest;

  /// Set HTTP response metadata (headers)
  httpResponse.setStatusCode(404);
  httpResponse.setHeader("Server", "AttoServer v1.0");
  httpResponse.setHeader("Content-type", "text/html; charset=ascii");

  /// Build the body of the response
  std::string title = "Not found";
  httpResponse.body()
      << "<!DOCTYPE html>\n"
      << "<html lang=\"en\">\n"
      << "  <meta charset=\"ascii\"/>\n"
      << "  <title>" << title << "</title>\n"
      << "  <style>body {font-family: monospace} h1 {color: red}</style>\n"
      << "  <h1>" << title << "</h1>\n"
      << "  <p>The requested resouce was not found on this server.</p>\n"
      << "  <hr><p><a href=\"/\">Homepage</a></p>\n"
      << "</html>\n";

  /// Send the response to the client (user agent)
  return httpResponse.send();
}
