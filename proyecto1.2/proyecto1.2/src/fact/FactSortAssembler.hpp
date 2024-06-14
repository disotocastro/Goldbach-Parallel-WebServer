// Copyright 2024 Diego Soto, Migueledo Nuñez, William Morales
// Universidad de Costa Rica. CC BY 4.0

#ifndef FACTSORTASSEMBLER
#define FACTSORTASSEMBLER

#include <map>
#include <vector>

#include "Assembler.hpp"
#include "FactNumber.hpp"
#include "HttpApp.hpp"
#include "Queue.hpp"

/**
 * @class FactSortAssembler
 * @brief Clase para organizar y ensamblar objetos FactNumber.
 *
 * La clase FactSortAssembler recibe objetos FactNumber, los agrupa en vectores
 * según su identificador, y los produce cuando todos los elementos esperados
 * para ese identificador han sido recibidos.
 */
class FactSortAssembler
    : public Assembler<FactNumber*, std::vector<FactNumber*>> {
 public:
  /**
   * @brief Método principal de ejecución de la clase.
   *
   * Este método inicia el proceso de consumo de objetos FactNumber
   * indefinidamente.
   * @return Código de salida del programa.
   */
  int run() override;

  /**
   * @brief Consume un objeto FactNumber.
   *
   * Este método procesa el objeto FactNumber recibido, actualizando los
   * vectores y contadores correspondientes, y produciendo el vector cuando
   * todos los elementos esperados han sido recibidos.
   * @param data Puntero al objeto FactNumber a ser procesado.
   */
  void consume(FactNumber* data) override;

  /**
   * @brief Continuamente consume datos de la cola.
   *
   * Este método consume datos de la cola de manera continua hasta
   * encontrar una condición de detención.
   *
   * @note Asume que la cola de consumo está inicializada.
   */
  void consumeForever() override;

 private:
  /**
   * @brief Mapa que asocia identificadores con vectores de objetos FactNumber.
   */
  std::map<int64_t, std::vector<FactNumber*>> map_vector;

  /**
   * @brief Mapa que asocia identificadores con contadores de elementos
   */
  std::map<int64_t, int> map_counter;
};

#endif  // FACTSORTASSEMBLER
