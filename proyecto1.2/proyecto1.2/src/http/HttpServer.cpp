// Copyright 2021 Jeisson Hidalgo-Cespedes. Universidad de Costa Rica. CC BY 4.0

#include "HttpServer.hpp"

#include <cassert>
#include <stdexcept>
#include <string>
#include <vector>

#include "HttpApp.hpp"
#include "HttpRequest.hpp"
#include "HttpResponse.hpp"
#include "Log.hpp"
#include "NetworkAddress.hpp"
#include "Queue.hpp"
#include "Socket.hpp"

// TODO(you): Implement connection handlers argument
const char* const usage =
    "Usage: webserv [port] [handlers]\n"
    "\n"
    "  port        Network port to listen incoming HTTP requests, "
    "default " DEFAULT_PORT
    "\n"
    "  handlers     Number of connection handler theads\n";

HttpServer::HttpServer() {
  // Crear cola de Sockets
  this->socketsQueue = new Queue<Socket>();
  // Crear instancia del dispatcher
  this->dispatcher = new HttpDispatcher();
  // Crear cola de consumo del dispatcher
  this->dispatcher->createOwnQueue();
}

HttpServer::~HttpServer() {}

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

      // Iniciar los hilos que forman parte de la cadena de produccion
      createThreads();
      this->dispatcher->startThread();

      this->listenForConnections(this->port);
      const NetworkAddress& address = this->getNetworkAddress();
      Log::append(Log::INFO, "webserver",
                  "Listening on " + address.getIP() + " port " +
                      std::to_string(address.getPort()));

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
    /// Detener los hilos que forman parte de la cadena de produccion
    // throw std::runtime_error("dispatcher: queue's key not found");
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

void HttpServer::createThreads() {
  // Asignar el tamaño del vector de ConnectionHandlers
  this->vectorHandlers.resize(this->handlers);
  for (int64_t i = 0; i < this->handlers; i++) {
    // Se inician la creación de los ConnectionHandlers
    this->vectorHandlers[i] = new HttpConnectionHandler();
    // Asignar la cola de consumo de los ConnectionHandlers
    this->vectorHandlers[i]->setConsumingQueue(this->socketsQueue);
    // Asignar la cola de produccion de los ConnectionHandlers
    this->vectorHandlers[i]->setProducingQueue(
        this->dispatcher->getConsumingQueue());
    // Inicar el hilo de ejecucion
    this->vectorHandlers[i]->startThread();
  }
}

void HttpServer::startApps() {
  for (size_t index = 0; index < this->applications.size(); ++index) {
    // Iniciar la webApp
    this->applications[index]->start();
    // Registrar en el dispatcher el Key y la de consumo del webApp
    this->dispatcher->registerRedirect(
        this->applications[index]->key,
        this->applications[index]->entranceQueue);
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
    } else if (argc == 2) {
      this->port = argv[1];
    }
  } catch (const std::exception& e) {
    Log::append(Log::INFO, "webserver", "stopping server connection");
    std::cerr << e.what() << '\n';
    std::cout << usage;
    exit(EXIT_FAILURE);
  }
  return true;
}

void HttpServer::handleClientConnection(Socket& client) {
  /**
   * Se encolan los sockets
   */
  this->socketsQueue->enqueue(client);
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
  for (int i = 0; i < handlers; i++) {
    this->socketsQueue->enqueue(Socket());
  }
  // Join
  for (int i = 0; i < handlers; i++) {
    this->vectorHandlers[i]->waitToFinish();
    delete this->vectorHandlers[i];
  }
  delete this->socketsQueue;

  this->dispatcher->waitToFinish();
  delete this->dispatcher;
}
