// Copyright 2024 William Morales <william.moralesfuentes@ucr.ac.cr>

#include <GoldSolver.hpp>
#include <cstdint>
#include <cstdlib>
#include <iostream>
#include <numbers.hpp>
#include <vector>

GoldSolver::GoldSolver() {}

GoldSolver::~GoldSolver() { free_memory(numbers); }

NumbersArray_t* GoldSolver::resolveGoldbach(
    std::vector<int64_t>& inputNumbers) {
  numbers = readNumbers(inputNumbers);
  prime_numbers(numbers);
  goldbach(numbers);
  return numbers;
}

void GoldSolver::goldbach(NumbersArray_t* NumbersArray) {
  // Itera sobre el rango de números asignado a este hilo
  for (int64_t index = 0; index < NumbersArray->counterNumbers; index++) {
    // Calcula las sumas de Goldbach para números pares e impares
    if (((NumbersArray->GoldbachSumsArray[index]->number) % 2) == 0) {
      goldbach_pair(NumbersArray, index);
    } else {
      goldbach_odd(NumbersArray, index);
    }

    NumbersArray->totalSums +=
        NumbersArray->GoldbachSumsArray[index]->sums_counter;
  }
}

void GoldSolver::prime_numbers(NumbersArray_t* NumbersArray) {
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

bool GoldSolver::is_prime(int64_t number) {
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

void GoldSolver::goldbach_pair(NumbersArray_t* NumbersArray, int64_t index) {
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
  for (int64_t i = 0; (NumbersArray->primeNumbers[i] < number) &&
                      (i < NumbersArray->counterPrimes);
       i++) {
    for (int64_t j = i; (NumbersArray->primeNumbers[j] < number) &&
                        (j < NumbersArray->counterPrimes);
         j++) {
      // Se verifica si la suma de dos números primos es igual al número dado
      if ((NumbersArray->primeNumbers[i] + NumbersArray->primeNumbers[j]) ==
          number) {
        // Se verifica si el tamaño actual de la matriz de sumas es suficiente
        if (size <= goldbachSumsCounter) {
          newSize = (size * 2);
          // Si no es suficiente, se duplica el tamaño
          for (int64_t i = 0; i < 3; i++) {
            goldbachSums[i] =
                (int64_t*)realloc(goldbachSums[i], newSize * sizeof(int64_t));
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

void GoldSolver::goldbach_odd(NumbersArray_t* NumbersArray, int64_t index) {
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
