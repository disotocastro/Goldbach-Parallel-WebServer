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
StartSimulation ahora utiliza MPI para distribuir las simulaciones entre múltiples procesos. Dentro de cada proceso, se utiliza OpenMP para paralelizar aún más el trabajo:

1. Se divide el número total de simulaciones entre los procesos MPI.
2. Cada proceso MPI maneja un subconjunto de simulaciones.
3. Dentro de cada proceso, se utiliza OpenMP para crear múltiples hilos y distribuir las simulaciones locales entre estos hilos.
4. Se utiliza una programación dinámica (`schedule(dynamic)`) para balancear la carga de trabajo entre los hilos.

RunSimulation crea una copia temporal de la matrix. En un ciclo Do-While, llama a la función "CalculateSimulation" con la estructura de datos simulación y los valores i, j que le corresponden.

## 4. CalculateSimulation
Mediante lógica, utiliza la fórmula que calcula el cambio de temperatura de una placa y la retorna.

## 5. Report
Recibe un vector de estructuras de datos "Simulación" ya resueltas. Imprime los datos en un archivo TSV con formatos legibles para el humano y llama a SaveMatrixFile.

## 6. SaveMatrixFile
Guarda el archivo de la placa, pero añade a su nombre "-" + "K iteración". Luego, guarda este archivo binario en la raíz del proyecto.

## 7. Main
El main ha sido modificado para incorporar MPI:

1. Se inicializa MPI al principio del programa.
2. Se obtiene el rango y tamaño de los procesos MPI.
3. La carga de datos y el inicio de las simulaciones ahora tienen en cuenta el uso de MPI.
4. Solo el proceso principal (rank 0) se encarga de generar el reporte final.

Estas modificaciones permiten una ejecución paralela tanto a nivel de procesos (MPI) como a nivel de hilos (OpenMP), lo que puede mejorar significativamente el rendimiento en sistemas con múltiples nodos y/o múltiples núcleos.