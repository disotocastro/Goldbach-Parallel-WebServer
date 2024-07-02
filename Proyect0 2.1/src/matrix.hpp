#ifndef MATRIX_HPP
#define MATRIX_HPP

#include <string>
#include <fstream>
#include <iostream>

class Matrix {
 public:
  unsigned long long rows;
  unsigned long long cols;
  double** data;

  // Default constructor
  Matrix() : rows(0), cols(0), data(nullptr) {}

  // Parameterized constructor
  Matrix(unsigned long long r, unsigned long long c) : rows(r), cols(c) {
    data = new double*[rows];
    for (unsigned long long i = 0; i < rows; ++i) {
      data[i] = new double[cols];
    }
  }

  // Destructor
  ~Matrix() {
    if (data) {
      for (unsigned long long i = 0; i < rows; ++i) {
        delete[] data[i];
      }
      delete[] data;
    }
  }
};
#endif  // MATRIX_HPP

