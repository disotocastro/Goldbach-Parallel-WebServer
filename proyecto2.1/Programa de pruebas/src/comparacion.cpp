#include "comparacion.hpp"

int main(int argc, char* argv[]) {
    // Verificar si se proporciona el nombre del archivo como argumento
    if (argc < 3) {
        std::cerr << "Error: Se requieren al menos dos nombres de archivo como argumentos." << std::endl;
        return EXIT_FAILURE;
    }

    std::string Matrix_name_1 = argv[1];
    std::string Matrix_name_2 = argv[2];

    // Verificar si se proporciona un tercer argumento (sensibilidad)
    if (argc < 4) {
        std::cerr << "Error: Se requiere un tercer argumento como sensibilidad (número entero)." << std::endl;
        return EXIT_FAILURE;
    }

    int sensibilidad = std::stoi(argv[3]);

    Matrix* matrix_1 = read_matrix_from_file(Matrix_name_1);
    Matrix* matrix_2 = read_matrix_from_file(Matrix_name_2);

    if (matrix_1 == nullptr || matrix_2 == nullptr) {
        std::cerr << "Error: No se pudieron leer las matrices desde los archivos." << std::endl;
        return EXIT_FAILURE;
    }

    if (matrix_1->rows != matrix_2->rows || matrix_1->cols != matrix_2->cols) {
        std::cout << "Las matrices son de dimensiones diferentes." << std::endl;
        return EXIT_FAILURE;
    }

    bool son_iguales = true;
    for (int i = 0; i < matrix_1->rows; i++) {
        for (int j = 0; j < matrix_1->cols; j++) {
            double diff = std::abs(matrix_1->data[i][j] - matrix_2->data[i][j]);
            if (diff > sensibilidad) {
                son_iguales = false;
                break;
            }
        }
        if (!son_iguales) {
            break;
        }
    }

    if (son_iguales) {
        std::cout << "Las matrices son iguales dentro de la sensibilidad especificada." << std::endl;
    } else {
        std::cout << "Las matrices son diferentes fuera de la sensibilidad especificada." << std::endl;
    }

    return EXIT_SUCCESS;
}

Matrix* read_matrix_from_file(const std::string& plate_name) {
  std::ifstream file(plate_name, std::ios::binary);
  if (!file.is_open()) {
    std::cerr << "Error: No se pudo abrir el archivo " << plate_name
              << std::endl;
    return nullptr;
  }

  int64_t rows = 0;
  int64_t cols = 0;

  // Leer la cantidad de filas
  file.read(reinterpret_cast<char*>(&rows), sizeof(rows));

  // Leer la cantidad de columnas
  file.read(reinterpret_cast<char*>(&cols), sizeof(cols));

  // Crear la matriz bidimensional
  Matrix* matrix = new Matrix(rows, cols);

  // Leer los datos de la matriz
  for (int64_t i = 0; i < matrix->rows; ++i) {
    file.read(reinterpret_cast<char*>(matrix->data[i]),
              matrix->cols * sizeof(double));
  }

  file.close();
  return matrix;
}