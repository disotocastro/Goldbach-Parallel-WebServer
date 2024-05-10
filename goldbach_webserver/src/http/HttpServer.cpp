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
      // Start waiting for connections
      this->listenForConnections(this->port);
      const NetworkAddress& address = this->getNetworkAddress();
      Log::append(Log::INFO, "webserver", "Listening on " + address.getIP()
        + " port " + std::to_string(address.getPort()));

      // TODO: Crear instancias de la cadena de producción ✔
      // TODO: Definir comunicacion, los elementos de la cadena de producción ✔
      // TODO: Iniciar comunicacion, los elementos de la cadena de producción ✔
      socketsQueue = new Queue<Socket>();
      // Crear el vector de los handlers
      this->vectorHandlers.resize(this->handlers);
      createThreads();        

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
    deleteThreads();
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

  /**
   * Mandejar los argumentos del servidor
   * 
   * Si no se ingresan de manera correcta, se cierra el programa y 
   * se imprime el uso de este mismo
   * 
  */
    try {
      if (argc == 3) {
        this->port = argv[1];
        this->handlers = atoi(argv[2]);
      } else if (argc==2) {
          this->port = argv[1];
      }
    } catch(const std::exception& e) {
      Log::append(Log::INFO, "webserver", "stopping server connection");
      std::cerr << e.what() << '\n';
      std::cout << usage; // TODO: end line?
      exit(EXIT_FAILURE);
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

void HttpServer::createThreads() {
  for (int64_t i = 0; i < this->handlers; i++) {
    // CREA UN HANDLER 
    this->vectorHandlers[i] = new HttpConnectionHandler(&this->applications);
    this->vectorHandlers[i]->setConsumingQueue(this->socketsQueue);
    this->vectorHandlers[i]->startThread();
  }
}

void HttpServer::deleteThreads() {
  /**
   * Si cuando llega la condicion de parada aun quedan sockets sin consumir
   * en la cola, se vacian.
   *
   * luego para cada Thread, se le hace join y se elimina
   *
   * Cuando el programa se vaya a detener, este necesita recibir una nueva
   * consulta para que se detenga por completo.
  */
  for (size_t i = 0; i < handlers; i++) {
    this->socketsQueue->enqueue(Socket());
  } 
  // Join
  for (size_t i = 0; i < handlers; i++) {
    this->vectorHandlers[i]->waitToFinish();
    delete this->vectorHandlers[i];
  }
  delete this->socketsQueue;
}
