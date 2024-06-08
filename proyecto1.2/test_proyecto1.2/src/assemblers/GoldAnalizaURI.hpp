// Copyright 2024 Diego Soto, Migueledo Nuñez, William Moraes
// Universidad de Costa Rica. CC BY 4.0

#ifndef GOLDANALIZAURI_HPP
#define GOLDANALIZAURI_HPP

#include <vector>

#include "Assembler.hpp"
#include "HttpApp.hpp"
#include "Queue.hpp"
#include "RequestResponseStruct.hpp"
#include "numbers.hpp"

class URI_Analyzer : public Assembler<RequestResponseStruct, Numbers_t*> {
 public:
  URI_Analyzer();
  explicit URI_Analyzer(Queue<RequestResponseStruct>* resquest_response_queue,
                        Queue<Numbers_t*>* numbers_t_queue);
  int run() override;
  void consume(RequestResponseStruct reqRes) override;

  /**
   * @brief Extracts numbers from the URI of the HTTP request.
   * @param httpRequest The HTTP request object.
   * @param numbersVector A vector to store the extracted numbers.
   * @return true if the numbers were successfully extracted, false otherwise.
   */
  bool getNumbersFromURI(HttpRequest& httpRequest,
                         std::vector<int64_t>& numbersVector);

  /**
   * @brief Crea una nueva estructura Numbers_t con el número especificado.
   * @param newNumber El número para crear la estructura.
   * @return Puntero a la nueva estructura Numbers_t creada.
   */
  Numbers_t* new_number(int64_t newNumber, int64_t index,
                        RequestResponseStruct reqRes);

  /**
   * @brief Lee los números de la entrada estándar y los almacena en un arreglo.
   * @return Puntero a la estructura NumbersArray_t que contiene los números
   * leídos.
   */
  NumbersArray_t* readNumbers(std::vector<int64_t>& inputNumbers,
                              RequestResponseStruct reqRes);

 protected:
};

#endif  // ANALIZAURI_HPP
