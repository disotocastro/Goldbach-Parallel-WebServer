// Copyright 2024 Diego Soto, Migueledo Nuñez, William Moraes
// Universidad de Costa Rica. CC BY 4.0

#ifndef GOLDHTML_HPP
#define GOLDHTML_HPP

#include <vector>

#include "Consumer.hpp"
#include "GoldSortAssembler.hpp"
#include "HttpApp.hpp"
#include "Socket.hpp"
#include "numbers.hpp"

/**
 * @class GoldHTML
 * @brief Clase para generar respuestas HTML para sumas de Goldbach.
 * 
 * Esta clase hereda de la clase Consumer y se encarga de generar respuestas
 * HTML para mostrar las sumas de Goldbach.
 */
class GoldHTML : public Consumer<std::vector<Numbers_t*>> {
 public:
 
  /**
   * @brief Ejecuta el consumidor.
   * 
   * Este método inicia el proceso de consumo y se ejecuta indefinidamente.
   * @return Un entero que representa el estado de salida.
   */
  int run() override;

  /**
   * @brief Consume los datos y genera la respuesta HTML.
   * 
   * Este método recibe los datos de las sumas de Goldbach y genera una respuesta
   * HTML para mostrarlas en una página web.
   * @param data Vector de punteros a los datos de las sumas de Goldbach.
   */
  void consume(std::vector<Numbers_t*> data) override;

  /**
   * @brief Envía una respuesta HTTP exitosa.
   * 
   * Este método envía una respuesta HTTP exitosa junto con el contenido HTML generado.
   * @param numbers Vector de punteros a los datos de las sumas de Goldbach.
   */
  void sendSuccessResponse(std::vector<Numbers_t*> numbers);

  /**
   * @brief Crea cadenas de texto para las sumas de Goldbach.
   * 
   * Este método toma los datos de las sumas de Goldbach y genera cadenas de texto
   * formateadas para mostrarlas en la respuesta HTML.
   * @param numbers Vector de punteros a los datos de las sumas de Goldbach.
   * @return Un vector de cadenas de texto formateadas para mostrar las sumas de Goldbach.
   */
  std::vector<std::string> create_strings(std::vector<Numbers_t*> numbers);
};

#endif  // GOLDHTML_HPP
