// Copyright 2024 Diego Soto, Migueledo Nuñez, William Morales
// Universidad de Costa Rica. CC BY 4.0

#ifndef GOLDSORTASSEMBLER_H
#define GOLDSORTASSEMBLER_H

#include <map>
#include <vector>

#include "Assembler.hpp"
#include "HttpApp.hpp"
#include "numbers.hpp"

/**
 * @class GoldSortAssembler
 * @brief Clase para organizar y ensamblar objetos Numbers_t.
 *
 * La clase GoldSortAssembler recibe objetos Numbers_t, los agrupa en vectores
 * según su identificador, y los produce cuando todos los elementos esperados
 * para ese identificador han sido recibidos.
 */
class GoldSortAssembler
    : public Assembler<Numbers_t*, std::vector<Numbers_t*>> {
 public:
  /**
   * @brief Método principal de ejecución de la clase.
   *
   * Este método inicia el proceso de consumo de objetos Numbers_t
   * indefinidamente.
   * @return Código de salida del programa.
   */
  int run() override;

  /**
   * @brief Consume un objeto Numbers_t.
   *
   * Este método procesa el objeto Numbers_t recibido, actualizando los
   * vectores y contadores correspondientes, y produciendo el vector cuando
   * todos los elementos esperados han sido recibidos.
   * @param data Puntero al objeto Numbers_t a ser procesado.
   */
  void consume(Numbers_t* data) override;

 private:
  /**
   * @brief Mapa que asocia identificadores con vectores de objetos Numbers_t.
   */
  std::map<int64_t, std::vector<Numbers_t*>> map_vector;

  /**
   * @brief Mapa que asocia identificadores con contadores de elementos
   */
  std::map<int64_t, int> map_counter;
};

#endif  // FACTSORTASSEMBLER
