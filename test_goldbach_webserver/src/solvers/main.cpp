// Copyright 2024 William Morales <william.moralesfuentes@ucr.ac.cr>

#include <goldbach_solver.hpp>
#include <numbers.hpp>


#include <cstdint>   // Equivalente a inttypes.h
#include <cstdio>    // Equivalente a stdio.h
#include <cstdlib>   // Equivalente a stdlib.h
#include <unistd.h>  // Funcionalidades específicas de Unix
#include <cinttypes>


/**
 * @brief Imprime las sumas de Goldbach para cada número en la lista.
 * @param NumbersArray Puntero a la estructura NumbersArray_t que contiene los números.
 */
void print_sums(NumbersArray_t* NumbersArray);

int main() {

   int64_t *arreglo = new int64_t[5];

    // Inicializar el arreglo con números hardcodeados
    arreglo[0] = 89;
    arreglo[1] = 456;
    arreglo[2] = -305;
    arreglo[3] = 976;
    arreglo[4] = 550;
    
  goldbach_solver prueba = goldbach_solver(arreglo, 5);

  for (int i = 0; i < prueba.numbers->GoldbachSumsArray[5]->sums_counter; i++)
  {
    prueba.numbers->GoldbachSumsArray[5]->goldbachSums[i][0];
    prueba.numbers->GoldbachSumsArray[5]->goldbachSums[i][1];
  }
  
  print_sums(prueba.numbers);

}

void print_sums(NumbersArray_t* NumbersArray) {
  printf("Total: %" PRId64 " numbers %" PRId64 " sums\n\n",
         NumbersArray->counterNumbers, NumbersArray->totalSums);

  for (int64_t index = 0; index < (NumbersArray->counterNumbers); index++) {
    // Si el número está fuera de los límites

    if (NumbersArray->GoldbachSumsArray[index]->number < 6) {
      // si hay que imprimir las sumas se imprime el "-"
      if (NumbersArray->GoldbachSumsArray[index]->printSums == true) {
        printf("-%" PRId64 ": NA\n",
               NumbersArray->GoldbachSumsArray[index]->number);
        // si no hay que imprimir las sumas mo se imprime el "-"
      } else {
        printf("%" PRId64 ": NA\n",
               NumbersArray->GoldbachSumsArray[index]->number);
      }

      // Si el número es válido
      // Si hay que imprimir las sumas
    } else if ((NumbersArray->GoldbachSumsArray[index]->printSums) == true) {
      printf("-%" PRId64 ": %" PRId64 " sums: ",
             NumbersArray->GoldbachSumsArray[index]->number,
             NumbersArray->GoldbachSumsArray[index]->sums_counter);

      // Si es par
      if (NumbersArray->GoldbachSumsArray[index]->number % 2 == 0) {
        for (int64_t sums = 0;
             sums < NumbersArray->GoldbachSumsArray[index]->sums_counter;
             sums++) {
          printf("%" PRId64 " + %" PRId64,
                 NumbersArray->GoldbachSumsArray[index]->goldbachSums[0][sums],
                 NumbersArray->GoldbachSumsArray[index]->goldbachSums[1][sums]);
          if (sums ==
              (NumbersArray->GoldbachSumsArray[index]->sums_counter) - 1) {
          } else {
            printf(", ");
          }
        }
        printf("\n");
        // Si es impar
      } else {
        for (int64_t sums = 0;
             sums < NumbersArray->GoldbachSumsArray[index]->sums_counter;
             sums++) {
          printf("%" PRId64 " + %" PRId64 " + %" PRId64,
                 NumbersArray->GoldbachSumsArray[index]->goldbachSums[0][sums],
                 NumbersArray->GoldbachSumsArray[index]->goldbachSums[1][sums],
                 NumbersArray->GoldbachSumsArray[index]->goldbachSums[2][sums]);

          if (sums ==
              (NumbersArray->GoldbachSumsArray[index]->sums_counter) - 1) {
          } else {
            printf(", ");
          }
        }
        printf("\n");
      }

      // Si no hay que imprimir las sumas
    } else {
      printf("%" PRId64 ": %" PRId64 " sums \n",
             NumbersArray->GoldbachSumsArray[index]->number,
             NumbersArray->GoldbachSumsArray[index]->sums_counter);
    }
  }
}
