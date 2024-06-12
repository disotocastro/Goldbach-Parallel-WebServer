// Copyright 2024 William Morales <william.moralesfuentes@ucr.ac.cr>

#include <GoldSolver.hpp>
#include <cstdint>
#include <cstdlib>
#include <iostream>
#include <numbers.hpp>
#include <vector>

GoldSolver::GoldSolver() {}

GoldSolver::~GoldSolver() {}

void GoldSolver::resolveGoldbach(Numbers_t* inputNumber) {
  std::vector<int64_t> primeNumbers = prime_numbers(inputNumber->number);

  // Calcula las sumas de Goldbach para números pares e impares
  if (((inputNumber->number) % 2) == 0) {
    goldbach_pair(inputNumber, primeNumbers);
  } else {
    goldbach_odd(inputNumber, primeNumbers);
  }
}

std::vector<int64_t> GoldSolver::prime_numbers(int64_t number) {
  std::vector<bool> isPrime(number + 1, true);

  // Criba de Eratóstenes
  for (int64_t p = 2; p * p <= number; p++) {
    if (isPrime[p]) {
      for (int64_t multiple = p * p; multiple <= number; multiple += p) {
        isPrime[multiple] = false;
      }
    }
  }

  // Almacenar los números primos en el array
  std::vector<int64_t> primeNumbers;
  for (int64_t i = 2; i <= number; i++) {
    if (isPrime[i]) {
      primeNumbers.push_back(i);
    }
  }

  return primeNumbers;
}

void GoldSolver::goldbach_pair(Numbers_t* inputNumber,
                               std::vector<int64_t> primeNumbers) {
  int64_t number = inputNumber->number;
  int64_t goldbachSumsCounter = 0;
  int64_t size = number / 3;

  // Allocate memory for storing Goldbach sums
  int64_t** goldbachSums = (int64_t**)calloc(2, sizeof(int64_t*));
  for (int64_t i = 0; i < 2; i++) {
    goldbachSums[i] = (int64_t*)calloc(size, sizeof(int64_t));
  }

  int64_t counterPrimes = primeNumbers.size();

  // Use two pointers to find pairs of prime numbers whose sum equals the given
  // number
  int64_t left = 0;
  int64_t right = counterPrimes - 1;

  while (left <= right) {
    int64_t sum = primeNumbers[left] + primeNumbers[right];

    if (sum == number) {
      // Check if the matrix needs to be resized
      if (goldbachSumsCounter >= size) {
        int64_t newSize = size * 2;
        for (int64_t i = 0; i < 2; i++) {
          int64_t* temp =
              (int64_t*)realloc(goldbachSums[i], newSize * sizeof(int64_t));
          goldbachSums[i] = temp;
        }
        size = newSize;
      }
      // Store the prime numbers that sum to the given number
      goldbachSums[0][goldbachSumsCounter] = primeNumbers[left];
      goldbachSums[1][goldbachSumsCounter] = primeNumbers[right];
      goldbachSumsCounter++;
      left++;
      right--;
    } else if (sum < number) {
      left++;
    } else {
      right--;
    }
  }
  // Store the results back into the NumbersArray structure
  inputNumber->goldbachSums = goldbachSums;
  inputNumber->sums_counter = goldbachSumsCounter;
}

void GoldSolver::goldbach_odd(Numbers_t* inputNumber,
                              std::vector<int64_t> primeNumbers) {
  int64_t number = inputNumber->number;
  int64_t goldbachSumsCounter = 0;
  int64_t size = number * 5;

  // Allocate memory for storing Goldbach sums
  int64_t** goldbachSums = (int64_t**)calloc(3, sizeof(int64_t*));
  for (int64_t i = 0; i < 3; i++) {
    goldbachSums[i] = (int64_t*)calloc(size, sizeof(int64_t));
  }

  int64_t counterPrimes = primeNumbers.size();

  for (int64_t i = 0; i < counterPrimes && primeNumbers[i] < number; i++) {
    // Use two pointers to find pairs of prime numbers whose sum equals the
    // given number
    int64_t left = i;
    int64_t right = counterPrimes - 1;

    while (left <= right) {
      int64_t sum = primeNumbers[i] + primeNumbers[left] + primeNumbers[right];

      if (sum == number) {
        // Check if the matrix needs to be resized
        if (goldbachSumsCounter >= size) {
          int64_t newSize = size * 2;
          for (int64_t j = 0; j < 3; j++) {
            int64_t* temp =
                (int64_t*)realloc(goldbachSums[j], newSize * sizeof(int64_t));
            goldbachSums[j] = temp;
          }
          size = newSize;
        }
        // Store the prime numbers that sum to the given number
        goldbachSums[0][goldbachSumsCounter] = primeNumbers[i];
        goldbachSums[1][goldbachSumsCounter] = primeNumbers[left];
        goldbachSums[2][goldbachSumsCounter] = primeNumbers[right];
        goldbachSumsCounter++;
        left++;
        right--;
      } else if (sum < number) {
        left++;
      } else {
        right--;
      }
    }
  }

  // Store the results back into the NumbersArray structure
  inputNumber->goldbachSums = goldbachSums;
  inputNumber->sums_counter = goldbachSumsCounter;
}
