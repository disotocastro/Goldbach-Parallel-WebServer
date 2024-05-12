// Copyright 2024 William Morales <william.moralesfuentes@ucr.ac.cr>

#ifndef GOLDSOLVER_HPP
#define GOLDSOLVER_HPP

#include <cstdint>
#include <numbers.hpp>
#include <vector>
#include <string>


class GoldSolver {

    public:

        GoldSolver( std::vector<int64_t>& inputNumbers);

        ~GoldSolver();

        /**
         * @brief Encuentra los números primos hasta el número más grande en la lista.
         * @param NumbersArray Puntero a la estructura NumbersArray_t que contiene los números.
         */
        void prime_numbers(NumbersArray_t* numbers_read);

        /**
         * @brief Verifica si un número dado es primo.
         * @param number El número a verificar.
         * @return true si el número es primo, false de lo contrario.
         */
        bool is_prime(int64_t number);

        /**
         * @brief Calcula las sumas de Goldbach para números impares.
         * @param NumbersArray Puntero a la estructura NumbersArray_t que contiene los números.
         * @param index Índice del número en el arreglo.
         */
        void goldbach_odd(NumbersArray_t* NumbersArray, int64_t index);

        /**
         * @brief Calcula las sumas de Goldbach para números pares.
         * @param NumbersArray Puntero a la estructura NumbersArray_t que contiene los números.
         * @param index Índice del número en el arreglo.
         */
        void goldbach_pair(NumbersArray_t* NumbersArray, int64_t index);

        /**
         * @brief Función de entrada para la ejecución de la tarea de Goldbach.
         * @param data Puntero a datos privados para la ejecución de la tarea.
         * @return NULL
         */
        void goldbach(NumbersArray_t* NumbersArray);

        void create_strings();

        NumbersArray_t* numbers;

        std::vector<std::string> stringSums;

};



#endif
