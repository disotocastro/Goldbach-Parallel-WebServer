#include "FactSortAssembler.hpp"

#include <iostream>
#include <map>

#include "FactSolverAssembler.hpp"

int FactSortAssembler::run() {
  this->consumeForever();
  return EXIT_SUCCESS;
}

void FactSortAssembler::consume(FactNumber* data) {
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
      std::vector<FactNumber*> producir = (*it).second;
      map_counter.erase(it_counter);
      map_vector.erase(it);
      produce(producir);
      return;
    }

  } else {
    /// Se agrega un nuevo vector si no existe
    std::vector<FactNumber*> nuevoVector;
    nuevoVector.resize(data->maxNumbers);
    nuevoVector[data->index] = data;

    /// Si solo se espera un dato para esta clave, producir el vector
    if (data->maxNumbers == 1) {
      produce(nuevoVector);
      std::cout << "Produci tamano uno" << std::endl;
      return;
    }

    /// Actualizar los mapas con la nueva clave y el nuevo vector
    map_counter[data->id] = data->maxNumbers;
    map_vector[data->id] = nuevoVector;
  }
}
