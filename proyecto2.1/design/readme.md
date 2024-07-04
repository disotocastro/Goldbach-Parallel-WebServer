# Explicación del Diseño

## 1. Job001.txt
El programa inicia recibiendo un archivo 'job001.txt', que contiene los "plates.bin" y los datos con los que se trabajarán estas placas.

## 2. LoadData
LoadData genera un vector de Simulaciones. Cada estructura "Simulación" contiene los datos necesarios para trabajar con ellas:
- Matrix
- Nombre de la placa
- Nombre del archivo
- Tiempo Delta
- Difusividad Térmica
- Tamaño de la placa
- Sensitividad
- Iteraciones K

Además, LoadData se encarga de leer los datos binarios de la Matrix que viene en la estructura de datos "Simulación".

## 3. StartSimulation
StartSimulation llama al método RunSimulation de manera concurrente, creando varios hilos de ejecución para cada placa. Cada hilo se encargará de trabajar en su placa correspondiente[i].

RunSimulation crea una copia temporal de la matrix. En un ciclo Do-While, llama a la función "CalculateSimulation" con la estructura de datos simulación y los valores i, j que le corresponden.

## 4. CalculateSimulation
Mediante lógica, utiliza la fórmula que calcula el cambio de temperatura de una placa y la retorna.

## 5. Report
Recibe un vector de estructuras de datos "Simulación" ya resueltas. Imprime los datos en un archivo TSV con formatos legibles para el humano y llama a SaveMatrixFile.

## 6. SaveMatrixFile
Guarda el archivo de la placa, pero añade a su nombre "-" + "K iteración". Luego, guarda este archivo binario en la raíz del proyecto.