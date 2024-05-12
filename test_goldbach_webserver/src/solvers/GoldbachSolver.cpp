// Copyright 2024 William Morales <william.moralesfuentes@ucr.ac.cr>

#include <GoldbachSolver.hpp>
#include <numbers.hpp>
#include <cstdint>   
#include <cstdlib>   

GoldbachSolver::GoldbachSolver(int64_t* inputNumbers, int64_t inputNumbersCount){
  numbers = readNumbers(inputNumbers,inputNumbersCount);
  prime_numbers(numbers);
  goldbach(numbers);
}

GoldbachSolver::~GoldbachSolver(){
  free_memory(numbers);
}

void GoldbachSolver::goldbach(NumbersArray_t* NumbersArray) {

  // Itera sobre el rango de números asignado a este hilo
  for (int64_t index = 0; index < NumbersArray->counterNumbers; index++) {
      // Calcula las sumas de Goldbach para números pares e impares
      if (((NumbersArray->GoldbachSumsArray[index]->number) % 2) == 0) {
        goldbach_pair(NumbersArray, index);
      } else {
        goldbach_odd(NumbersArray, index);
      }

      NumbersArray->totalSums += NumbersArray->GoldbachSumsArray[index]->sums_counter;
  }
}

void GoldbachSolver::prime_numbers(NumbersArray_t* NumbersArray) {
  int64_t* primeNumbers = NumbersArray->primeNumbers;
  int64_t maxPrimeCount = NumbersArray->largestNumber / 2;
  // Se reserva memoria para almacenar los números primos
  primeNumbers = (int64_t*)calloc(maxPrimeCount, sizeof(int64_t));

  if (primeNumbers == NULL) {
    // Manejo de errores en caso de fallo de asignación de memoria
    // return NULL;
  }

  primeNumbers[0] = 2;
  int64_t indexArray = 1;
  for (int64_t number = 3; number < NumbersArray->largestNumber; number += 2) {
    // Itera sobre todos los números impares hasta el número más grande en la
    // lista
    if (is_prime(number)) {
      primeNumbers[indexArray] = number;
      indexArray++;
    }
  }

  // Actualiza el contador de números primos en la lista
  NumbersArray->counterPrimes = indexArray;
  NumbersArray->primeNumbers = primeNumbers;
}

bool GoldbachSolver::is_prime(int64_t number) {
  bool prime = true;
  for (int64_t testNumber = 3; testNumber < number; testNumber += 2) {
    // Comprueba si el número es divisible por algún número impar menor que él
    if ((number % testNumber == 0)) {
      prime = false;
      break;
    }
  }
  return prime;
}

void GoldbachSolver::goldbach_pair(NumbersArray_t* NumbersArray, int64_t index) {
  int64_t newSize = 0;
  int64_t number = NumbersArray->GoldbachSumsArray[index]->number;
  int64_t goldbachSumsCounter = 0;
  int64_t size = (NumbersArray->GoldbachSumsArray[index]->number) / 3;

  // Se reserva memoria para almacenar las sumas de Goldbach
  int64_t** goldbachSums = (int64_t**)calloc(2, sizeof(int64_t*));
  for (int64_t i = 0; i < 2; i++) {
    goldbachSums[i] = (int64_t*)calloc(size, sizeof(int64_t));
  }

  // Bucle para encontrar las sumas de Goldbach
  for (int64_t i = 0; (NumbersArray->primeNumbers[i] < number) && (i < NumbersArray->counterPrimes); i++) {
    for (int64_t j = i; (NumbersArray->primeNumbers[j] < number) && (j < NumbersArray->counterPrimes); j++) {
      // Se verifica si la suma de dos números primos es igual al número dado
      if ((NumbersArray->primeNumbers[i] + NumbersArray->primeNumbers[j]) ==
          number) {
        // Se verifica si el tamaño actual de la matriz de sumas es suficiente
        if (size <= goldbachSumsCounter) {
          newSize = (size * 2);
          // Si no es suficiente, se duplica el tamaño
          for (int64_t i = 0; i < 3; i++) {
            goldbachSums[i] = (int64_t*)realloc(goldbachSums[i],
              newSize * sizeof(int64_t));
          }
          size = newSize;
        }
        // Se almacenan los números primos que suman el número dado
        goldbachSums[0][goldbachSumsCounter] = NumbersArray->primeNumbers[i];
        goldbachSums[1][goldbachSumsCounter] = NumbersArray->primeNumbers[j];
        goldbachSumsCounter++;
      }
    }
  }
  // Se asignan las sumas de Goldbach y el contador de sumas al registro
  NumbersArray->GoldbachSumsArray[index]->goldbachSums = goldbachSums;
  NumbersArray->GoldbachSumsArray[index]->sums_counter = goldbachSumsCounter;
}

void GoldbachSolver::goldbach_odd(NumbersArray_t* NumbersArray, int64_t index) {
  int64_t newSize = 0;
  int64_t number = NumbersArray->GoldbachSumsArray[index]->number;
  int64_t goldbachSumsCounter = 0;
  int64_t size = (NumbersArray->GoldbachSumsArray[index]->number) * 5;

  // Se reserva memoria para almacenar las sumas de Goldbach
  int64_t** goldbachSums = (int64_t**)calloc(3, sizeof(int64_t*));
  for (int64_t i = 0; i < 3; i++) {
    goldbachSums[i] = (int64_t*)calloc(size, sizeof(int64_t));
  }

  // Bucle para encontrar las sumas de Goldbach
  for (int64_t i = 0; (NumbersArray->primeNumbers[i] < number) &&
                      (i < NumbersArray->counterPrimes);
       i++) {
    for (int64_t j = i; (NumbersArray->primeNumbers[j] < number) &&
                        (j < NumbersArray->counterPrimes);
         j++) {
      for (int64_t k = j; (NumbersArray->primeNumbers[k] < number) &&
                          (k < NumbersArray->counterPrimes);
           k++) {
        // Se verifica si la suma de tres números primos es igual al número dado
        if ((NumbersArray->primeNumbers[i] + NumbersArray->primeNumbers[j] +
             NumbersArray->primeNumbers[k]) == number) {
          // Se verifica si el tamaño actual de la matriz de sumas es suficiente
          if (size <= goldbachSumsCounter) {
            // Si no es suficiente, se duplica el tamaño
            newSize = (size * 2);
            for (int64_t i = 0; i < 3; i++) {
              goldbachSums[i] =
                  (int64_t*)realloc(goldbachSums[i], newSize * sizeof(int64_t));
            }
            size = newSize;
          }
          // Se almacenan los números primos que suman el número dado
          goldbachSums[0][goldbachSumsCounter] = NumbersArray->primeNumbers[i];
          goldbachSums[1][goldbachSumsCounter] = NumbersArray->primeNumbers[j];
          goldbachSums[2][goldbachSumsCounter] = NumbersArray->primeNumbers[k];

          goldbachSumsCounter++;
        }
      }
    }
  }
  // Se asignan las sumas de Goldbach y el contador de sumas al registro
  NumbersArray->GoldbachSumsArray[index]->goldbachSums = goldbachSums;
  NumbersArray->GoldbachSumsArray[index]->sums_counter = goldbachSumsCounter;
}


// // Copyright 2024 William Morales <william.moralesfuentes@ucr.ac.cr>

// #include <GoldbachSolver.hpp>
// #include <numbers.hpp>


// #include <cstdint>   // Equivalente a inttypes.h
// #include <cstdio>    // Equivalente a stdio.h
// #include <cstdlib>   // Equivalente a stdlib.h
// #include <unistd.h>  // Funcionalidades específicas de Unix
// #include <cinttypes>


// /**
//  * @brief Imprime las sumas de Goldbach para cada número en la lista.
//  * @param NumbersArray Puntero a la estructura NumbersArray_t que contiene los números.
//  */
// void print_sums(NumbersArray_t* NumbersArray);

// int main() {

//    int64_t *arreglo = new int64_t[5];

//     // Inicializar el arreglo con números hardcodeados
//     arreglo[0] = 89;
//     arreglo[1] = 456;
//     arreglo[2] = -305;
//     arreglo[3] = 976;
//     arreglo[4] = 550;
    
//   GoldbachSolver prueba = GoldbachSolver(arreglo, 5);

//   for (int i = 0; i < prueba.numbers->GoldbachSumsArray[5]->sums_counter; i++)
//   {
//     prueba.numbers->GoldbachSumsArray[5]->goldbachSums[i][0];
//     prueba.numbers->GoldbachSumsArray[5]->goldbachSums[i][1];
//   }
  
//   print_sums(prueba.numbers);

// }

// void print_sums(NumbersArray_t* NumbersArray) {
//   printf("Total: %" PRId64 " numbers %" PRId64 " sums\n\n",
//          NumbersArray->counterNumbers, NumbersArray->totalSums);

//   for (int64_t index = 0; index < (NumbersArray->counterNumbers); index++) {
//     // Si el número está fuera de los límites

//     if (NumbersArray->GoldbachSumsArray[index]->number < 6) {
//       // si hay que imprimir las sumas se imprime el "-"
//       if (NumbersArray->GoldbachSumsArray[index]->printSums == true) {
//         printf("-%" PRId64 ": NA\n",
//                NumbersArray->GoldbachSumsArray[index]->number);
//         // si no hay que imprimir las sumas mo se imprime el "-"
//       } else {
//         printf("%" PRId64 ": NA\n",
//                NumbersArray->GoldbachSumsArray[index]->number);
//       }

//       // Si el número es válido
//       // Si hay que imprimir las sumas
//     } else if ((NumbersArray->GoldbachSumsArray[index]->printSums) == true) {
//       printf("-%" PRId64 ": %" PRId64 " sums: ",
//              NumbersArray->GoldbachSumsArray[index]->number,
//              NumbersArray->GoldbachSumsArray[index]->sums_counter);

//       // Si es par
//       if (NumbersArray->GoldbachSumsArray[index]->number % 2 == 0) {
//         for (int64_t sums = 0;
//              sums < NumbersArray->GoldbachSumsArray[index]->sums_counter;
//              sums++) {
//           printf("%" PRId64 " + %" PRId64,
//                  NumbersArray->GoldbachSumsArray[index]->goldbachSums[0][sums],
//                  NumbersArray->GoldbachSumsArray[index]->goldbachSums[1][sums]);
//           if (sums ==
//               (NumbersArray->GoldbachSumsArray[index]->sums_counter) - 1) {
//           } else {
//             printf(", ");
//           }
//         }
//         printf("\n");
//         // Si es impar
//       } else {
//         for (int64_t sums = 0;
//              sums < NumbersArray->GoldbachSumsArray[index]->sums_counter;
//              sums++) {
//           printf("%" PRId64 " + %" PRId64 " + %" PRId64,
//                  NumbersArray->GoldbachSumsArray[index]->goldbachSums[0][sums],
//                  NumbersArray->GoldbachSumsArray[index]->goldbachSums[1][sums],
//                  NumbersArray->GoldbachSumsArray[index]->goldbachSums[2][sums]);

//           if (sums ==
//               (NumbersArray->GoldbachSumsArray[index]->sums_counter) - 1) {
//           } else {
//             printf(", ");
//           }
//         }
//         printf("\n");
//       }

//       // Si no hay que imprimir las sumas
//     } else {
//       printf("%" PRId64 ": %" PRId64 " sums \n",
//              NumbersArray->GoldbachSumsArray[index]->number,
//              NumbersArray->GoldbachSumsArray[index]->sums_counter);
//     }
//   }
// }
