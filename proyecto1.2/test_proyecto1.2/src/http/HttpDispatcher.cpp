#include "HttpDispatcher.hpp"

#include "RequestResponseStruct.hpp"

HttpDispatcher::HttpDispatcher() {}

HttpDispatcher::~HttpDispatcher() {}

int HttpDispatcher::run() {
  this->consumeForever();

  // condicion de parada
  for (const auto& pair : this->toQueues) {
    pair.second->enqueue(this->stopCondition);
  }

  return EXIT_SUCCESS;
}

// Analizador de URI
std::string HttpDispatcher::extractKey(
    const RequestResponseStruct& package) const {
  // Iterar sobre las colas registradas
  for (const auto& pair : this->toQueues) {
    // Verificar si el URI de la solicitud HTTP entrante comienza con la clave
    // de la cola actual
    if (package.httpRequest->getURI().rfind(pair.first, 0) == 0) {
      // Si la solicitud comienza con la clave, devolver la clave
      return pair.first;
    }
  }
  // Si no se encuentra coincidencia, devolver una cadena vacía
  return "";
}

void HttpDispatcher::consume(RequestResponseStruct data) {
  // Determinar la clave basada en el URI de la solicitud HTTP
  std::string key;

  key = this->extractKey(data);

  // Verificar si la clave extraída está en el mapa `toQueues`
  const auto& iterador = this->toQueues.find(key);
  if (iterador == this->toQueues.end()) {
    // Si la clave no está en el mapa, enviar una respuesta 404 Not Found al
    // cliente
    this->serverNotFound(data);
    // throw std::runtime_error("dispatcher: queue's key not found");
  } else {
    // Si la clave está en el mapa, encolar los datos (`solicitudRespuesta`)
    // en la cola correspondiente
    iterador->second->enqueue(data);
  }
}

void HttpDispatcher::stop() {}

void HttpDispatcher::serverNotFound(RequestResponseStruct& data) const {
  // Set the status code and headers of the response
  data.httpResponse->setStatusCode(404);
  data.httpResponse->setHeader("Server", "AttoServer v1.0");
  data.httpResponse->setHeader("Content-type", "text/html; charset=ascii");

  // Build the body of the response
  std::string title = "Not found";
  data.httpResponse->body()
      << "<!DOCTYPE html>\n"
      << "<html lang=\"en\">\n"
      << "  <meta charset=\"ascii\"/>\n"
      << "  <title>" << title << "</title>\n"
      << "  <style>body {font-family: monospace} h1 {color: red}</style>\n"
      << "  <h1>" << title << "</h1>\n"
      << "  <p>The requested resouce was not found on this server.</p>\n"
      << "  <hr><p><a href=\"/\">Homepage</a></p>\n"
      << "</html>\n";

  // Send the HTTP response
  data.httpResponse->send();
}
