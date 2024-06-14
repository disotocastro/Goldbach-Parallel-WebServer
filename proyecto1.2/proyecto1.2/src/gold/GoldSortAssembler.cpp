// Copyright 2024 Diego Soto, Migueledo Nuñez, William Morales
// Universidad de Costa Rica. CC BY 4.0

#include "GoldSortAssembler.hpp"

int GoldSortAssembler::run() {
  this->consumeForever();
  produce(std::vector<Numbers_t*>());
  return EXIT_SUCCESS;
}

void GoldSortAssembler::consume(Numbers_t* data) {
  /// Buscar la clave en el mapa de contadores
  auto it_counter = map_counter.find(data->id);

  /// Buscar la clave en el mapa de vectores
  auto it = map_vector.find(data->id);

  /// Verificar si la clave ya existe en el mapa de vectores
  if (it != map_vector.end()) {
    /// Actualizar el vector asociado con los nuevos datos
    (*it).second[data->index] = data;
    /// Reducir el contador asociado a la clave
    (*it_counter).second--;

    /// Verificar si se han recibido todos los datos correspondientes a esta
    /// clave
    if ((*it_counter).second == 0) {
      /// Si se han recibido todos los datos, producir el vector y eliminar la
      /// entrada de los mapas
      std::vector<Numbers_t*> producir = (*it).second;
      map_counter.erase(it_counter);
      map_vector.erase(it);
      produce(producir);
      return;
    }

  } else {
    /// Se agrega un nuevo vector si no existe
    std::vector<Numbers_t*> nuevoVector;
    nuevoVector.resize(data->maxNumbers);
    nuevoVector[data->index] = data;

    /// Si solo se espera un dato para esta clave, producir el vector
    if (data->maxNumbers == 1) {
      produce(nuevoVector);
      return;
    }

    /// Actualizar los mapas con la nueva clave y el nuevo vector
    map_counter[data->id] = data->maxNumbers - 1;
    map_vector[data->id] = nuevoVector;
  }
}

void GoldSortAssembler::consumeForever() {
  assert(this->consumingQueue);
  while (true) {
    // Get the next data to consume, or block while queue is empty
    Numbers_t* data = this->consumingQueue->dequeue();
    // If data is the stop condition, stop the loop
    if (data->id == 0) {
      break;
    }
    // Process this data
    this->consume(data);
  }
}
