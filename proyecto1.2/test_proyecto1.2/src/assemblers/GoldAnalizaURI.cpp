
#include "GoldAnalizaURI.hpp"

#include <regex>
#include <string>

int URI_Analyzer::run() {
  this->consumeForever();
  return EXIT_SUCCESS;
}

URI_Analyzer::URI_Analyzer(
    Queue<RequestResponseStruct>* resquest_response_queue,
    Queue<Numbers_t*>* numbers_t_queue) {
  this->setConsumingQueue(resquest_response_queue);
  this->setProducingQueue(numbers_t_queue);
}

bool URI_Analyzer::getNumbersFromURI(HttpRequest& httpRequest,
                                     std::vector<int64_t>& numbersVector) {
  if (size_t pos = httpRequest.getURI().find("number=")) {
    std::string str = "";
    int longitud = 0;

    std::string numbersString = httpRequest.getURI().substr(pos + 7);
    // Uniformar el URI para que el separador sea espacio
    std::regex coma("%..");  // símbolo porcentaje y dos caracteres cualquiera
    std::string nuevoUri = std::regex_replace(numbersString, coma, " ");
    // Expresión regular para buscar números enteros
    std::regex patron("-?[0-9]+");
    std::smatch matches;
    std::string::const_iterator ini = nuevoUri.begin();
    std::string::const_iterator fin = nuevoUri.end();
    // Buscar números en el URI modificado
    while (std::regex_search(ini, fin, matches, patron)) {
      str = matches.str();
      longitud = str.size();
      if (longitud > 19) {
        return false;  // Hay un error, número demasiado grande
      }
      int valor = std::stoll(matches[0].str());
      numbersVector.push_back(valor);
      ini = matches.suffix().first;
    }
    return true;
  } else {
    return false;  // Hay un error, no se encontró la cadena "number="
  }
}

void URI_Analyzer::consume(RequestResponseStruct reqRes) {
  std::vector<int64_t> numbersVector;

  getNumbersFromURI(*reqRes.httpRequest, numbersVector);

  readNumbers(numbersVector, reqRes);
}

NumbersArray_t* URI_Analyzer::readNumbers(std::vector<int64_t>& inputNumbers,
                                          RequestResponseStruct reqRes) {
  /// Crear el arreglo para almacenar los numeros.
  NumbersArray_t* numbers = (NumbersArray_t*)malloc(sizeof(NumbersArray_t));
  numbers->GoldbachSumsArray = nullptr;
  numbers->counterNumbers = inputNumbers.size();
  numbers->totalSums = 0;

  // Lee los números de la entrada estándar y los almacena en la lista
  for (size_t i = 0; i < inputNumbers.size(); i++) {
    this->producingQueue->enqueue(new_number(inputNumbers[i], i, reqRes));
  }
  return numbers;
}

Numbers_t* URI_Analyzer::new_number(int64_t newNumber, int64_t index,
                                    RequestResponseStruct reqRes) {
  // Asigna memoria para el nuevo objeto Numbers_t
  Numbers_t* newData = (Numbers_t*)malloc(sizeof(Numbers_t));
  // Inicializa los campos del objeto con los valores predeterminados
  newData->number = newNumber;
  newData->printSums = false;
  newData->sums_counter = 0;
  newData->goldbachSums = NULL;
  newData->index = index;
  newData->id = reqRes.id;
  newData->httpResponse = *reqRes.httpResponse;

  /** Si el número es negativo, establece la bandera de impresión de sumas y
  convierte el número en positivo */
  if (newNumber < 0) {
    newData->printSums = true;
    newData->number = -newNumber;
  }
  // Retorna un puntero al nuevo objeto Numbers_t creado
  return newData;
}
