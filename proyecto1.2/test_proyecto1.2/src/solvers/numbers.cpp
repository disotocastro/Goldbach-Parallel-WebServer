// Copyright 2024 William Morales <william.moralesfuentes@ucr.ac.cr>

#include <stdio.h>
#include <stdlib.h>

#include <numbers.hpp>

void free_memory(Numbers_t* inputNumber) {
  if ((inputNumber->number) % 2 == 0) {
    free(inputNumber->goldbachSums[0]);
    free(inputNumber->goldbachSums[1]);
    free(inputNumber->goldbachSums);
  } else {
    free(inputNumber->goldbachSums[0]);
    free(inputNumber->goldbachSums[1]);
    free(inputNumber->goldbachSums[2]);
    free(inputNumber->goldbachSums);
  }
  free(inputNumber);
}
