// Copyright 2021 Jeisson Hidalgo-Cespedes. Universidad de Costa Rica. CC BY 4.0

#include <cassert>
#include <stdexcept>
#include <string>
#include <vector>

#include "HttpApp.hpp"
#include "HttpServer.hpp"
#include "HttpRequest.hpp"
#include "HttpResponse.hpp"
#include "Log.hpp"
#include "Queue.hpp"
#include "NetworkAddress.hpp"
#include "Socket.hpp"

// TODO(you): Implement connection handlers argument
const char* const usage =
  "Usage: webserv [port] [handlers]\n"
  "\n"
  "  port        Network port to listen incoming HTTP requests, default "
    DEFAULT_PORT "\n"
  "  handlers     Number of connection handler theads\n";

HttpServer::HttpServer() {
}

HttpServer::~HttpServer() {
}

// Método para hacer singlenton el servidor, solo existe una instancia de él
HttpServer& HttpServer::getInstance() {
  static HttpServer httpServer;
  return httpServer;
}

void HttpServer::listenForever(const char* port) {
  return TcpServer::listenForever(port);
}

void HttpServer::chainWebApp(HttpApp* application) {
  assert(application);
  this->applications.push_back(application);
}

int HttpServer::run(int argc, char* argv[]) {
  bool stopApps = false;
  try {
    if (this->analyzeArguments(argc, argv)) {
      // Start the log service
      Log::getInstance().start();

      // Start all web applications
      this->startApps();
      stopApps = true;

      // TODO: Crear instancias de la cadena de producción
      // TODO: Definir comunicacion, los elementos de la cadena de producción


      // TODO: Iniciar comunicacion, los elementos de la cadena de producción 

      // Start waiting for connections
      // TODO: Log the main thread id
      this->listenForConnections(this->port);
      const NetworkAddress& address = this->getNetworkAddress();
      Log::append(Log::INFO, "webserver", "Listening on " + address.getIP()
        + " port " + std::to_string(address.getPort()));

      // Accept all client connections. The main process will get blocked
      // running this method and will not return. When HttpServer::stop() is
      // called from another execution thread, an exception will be launched
      // that stops the acceptAllConnections() invocation and enters in the
      // catch below. Then, the main thread can continue stopping apps,
      /// finishing the server and any further cleaning it requires.
      this->acceptAllConnections();
    }
  } catch (const std::runtime_error& error) {
    std::cerr << "error: " << error.what() << std::endl;

    /**
     * Cuando el programa se vaya a detener, este necesita recibir una nueva
     * consulta para que se detenga por completo.
     * 
     * 
     * Para terminar, se tiene que mandar otro socket y despues caerse
     * TODO: Agregar: WAIT TO FINISH
    */
  }

  // If applications were started
  if (stopApps) {
    this->stopApps();
  }

  // Stop the log service
  Log::getInstance().stop();
  return EXIT_SUCCESS;
}

void HttpServer::startApps() {
  for (size_t index = 0; index < this->applications.size(); ++index) {
    this->applications[index]->start();
  }
}

void HttpServer::stopApps() {
  // Stop web applications. Give them an opportunity to clean up
  for (size_t index = 0; index < this->applications.size(); ++index) {
    this->applications[index]->stop();
  }
}

void HttpServer::stop() {
  // Stop listening for incoming client connection requests. When stopListing()
  // method is called -maybe by a secondary thread-, the web server -running
  // by the main thread- will stop executing the acceptAllConnections() method.
  this->stopListening();
}

bool HttpServer::analyzeArguments(int argc, char* argv[]) {
  // Traverse all arguments
  for (int index = 1; index < argc; ++index) {
    const std::string argument = argv[index];
    if (argument.find("help") != std::string::npos) {
      std::cout << usage;
      return false;
    }
  }

  if (argc >= 2) {
    this->port = argv[1];
  }

  return true;
}

void HttpServer::handleClientConnection(Socket& client) {
  // TODO: Make this method concurrent. Store client connections (sockets)
  // into a collection (e.g thread-safe queue) and stop in web server

  /**
   * Se encolan los sockets
   * 
  */
  this->socketsQueue->enqueue(client);
}

