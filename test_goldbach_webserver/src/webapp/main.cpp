// Copyright 2021 Jeisson Hidalgo-Cespedes. Universidad de Costa Rica. CC BY 4.0
// Serial web server's initial code for parallelization

#ifdef WEBSERVER

#include <iostream>
#include <csignal>

#include "HttpServer.hpp"
#include "GoldWebApp.hpp"
#include "FactWebApp.hpp"
#include "Log.hpp"

void signalHandler(int signal);
/// Start the web server
int main(int argc, char* argv[]) {
  // (Ctrl+C)
  signal(SIGINT, signalHandler);
  // (kill)
  signal(SIGTERM, signalHandler);
  // Create the web server singleton
  HttpServer& httpServer = HttpServer::getInstance();
  // Create a factorization web application, and other apps if you want
  FactWebApp factWebApp;
  GoldWebApp goldWebApp;
  // Register the web application(s) with the web server
  httpServer.chainWebApp(&factWebApp);
  httpServer.chainWebApp(&goldWebApp);
  // Run the web server
  return httpServer.run(argc, argv);
}

void signalHandler(int signal) {
  std::cout << "\n\nSignal " << signal << " by thread ID:  "
  << std::this_thread::get_id() << std::endl<< std::endl;
  HttpServer::getInstance().stop();
  Log::append(Log::INFO, "webserver", "stopping server connection");
  exit(signal);
}

#endif  // WEBSERVER

