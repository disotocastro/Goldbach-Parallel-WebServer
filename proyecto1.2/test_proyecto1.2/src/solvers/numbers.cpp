// Copyright 2024 William Morales <william.moralesfuentes@ucr.ac.cr>

#include <stdio.h>
#include <stdlib.h>

#include <numbers.hpp>


// NumbersArray_t* readNumbers(std::vector<int64_t>& inputNumbers) {
//   // Tamaño inicial del arreglo
//   int64_t size = 10;
//   /// Crear el arreglo para almacenar los numeros.
//   NumbersArray_t* numbers = (NumbersArray_t*)malloc(sizeof(NumbersArray_t));
//   numbers->GoldbachSumsArray = (Numbers_t**)malloc(size * (sizeof(Numbers_t*)));
//   numbers->counterNumbers = 0;
//   numbers->largestNumber = 0;
//   numbers->totalSums = 0;
//   numbers->counterPrimes = 0;

//   // Lee los números de la entrada estándar y los almacena en la lista
//   for (size_t i = 0; i < inputNumbers.size(); i++) {
//     // Verifica si se necesita expandir el tamaño del arreglo
//     if (numbers->counterNumbers >= size) {
//       size = size * 2;
//       numbers->GoldbachSumsArray = (Numbers_t**)realloc(
//           numbers->GoldbachSumsArray, (size) * sizeof(Numbers_t*));
//     }
//     // Crea un nuevo objeto `Numbers_t` para almacenar el número leído
//     numbers->GoldbachSumsArray[numbers->counterNumbers] =
//         new_number(inputNumbers[i]);

//     // Si el número es negativo, se convierte en positivo para determinar el
//     // más grande
//     if (inputNumbers[i] < 0) {
//       inputNumbers[i] = -inputNumbers[i];
//     }

//     // Actualiza el valor del número más grande leído
//     if (inputNumbers[i] > numbers->largestNumber) {
//       numbers->largestNumber = inputNumbers[i];
//     }
//     // Incrementa el contador de números leídos
//     numbers->counterNumbers++;
//   }
//   return numbers;
// }

// Numbers_t* new_number(int64_t newNumber) {
//   // Asigna memoria para el nuevo objeto Numbers_t
//   Numbers_t* newData = (Numbers_t*)malloc(sizeof(Numbers_t));
//   // Inicializa los campos del objeto con los valores predeterminados
//   newData->number = newNumber;
//   newData->printSums = false;
//   newData->sums_counter = 0;
//   newData->goldbachSums = NULL;

//   /** Si el número es negativo, establece la bandera de impresión de sumas y
//   convierte el número en positivo */
//   if (newNumber < 0) {
//     newData->printSums = true;
//     newData->number = -newNumber;
//   }
//   // Retorna un puntero al nuevo objeto Numbers_t creado
//   return newData;
// }

void free_memory(NumbersArray_t* NumbersArray) {
  free(NumbersArray->primeNumbers);
  for (int64_t i = 0; i < NumbersArray->counterNumbers; i++) {
    if ((NumbersArray->GoldbachSumsArray[i]->number) % 2 == 0) {
      free(NumbersArray->GoldbachSumsArray[i]->goldbachSums[0]);
      free(NumbersArray->GoldbachSumsArray[i]->goldbachSums[1]);
      free(NumbersArray->GoldbachSumsArray[i]->goldbachSums);
      free(NumbersArray->GoldbachSumsArray[i]);
    } else {
      free(NumbersArray->GoldbachSumsArray[i]->goldbachSums[0]);
      free(NumbersArray->GoldbachSumsArray[i]->goldbachSums[1]);
      free(NumbersArray->GoldbachSumsArray[i]->goldbachSums[2]);
      free(NumbersArray->GoldbachSumsArray[i]->goldbachSums);
      free(NumbersArray->GoldbachSumsArray[i]);
    }
  }
  free(NumbersArray->GoldbachSumsArray);
  free(NumbersArray);
}
