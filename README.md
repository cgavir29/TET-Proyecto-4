# TET Proyecto 4

## 1. Link Drive

https://drive.google.com/drive/folders/1piiqewvpliQUFRVZYRBsc58DWFiEK1KA?usp=sharing

## 2. Algoritmo Secuencial

### 2.1. Descripción del Algoritmo

Se tiene inicialmente un documento de texto de entrada donde se contiene el arreglo de números de enteros que van a ser ordenados.
Se procesa este archivo y se almacenan los datos en un arreglo y este se envía al algoritmo merge sort para empezar su procesamiento.

El algoritmo sigue de la siguiente forma:

- Si la longitud del arreglo es 0 ó 1 ya estaba ordenado entonces no se realiza ningún otro procedimiento. Si no es así se ejecutan los siguientes puntos.
- Se divide el arreglo desordenado en dos sub-arreglos de la mitad del tamaño.
- Se procede a ordenar cada sub-arreglo recursivamente aplicando el mismo algoritmo de división.
- Finalmente se mezclan los dos sub-arreglos obtenidas en uno solo ordenado y así se completaría todo el proceso.

Para finalizar, se recorre eel arreglo ordenado y se escribe en un documento de texto para entregar el resultado.

### 2.2. Pseudocódigo

![imagenes-1](images/seudocode.PNG)

### 2.3. Guía de Compilación

Para comílar el programa utilizamos el siguiente Makefile:

![imagenes-1](images/compile.png)

Para ejecutarlo corremos el comando: `make` como se ve en la imagen.

### 2.4. Ejecución

Ejecutamos el programa que nos queda despues de compilar pasandole como argumento algun archivo de texto con los datos de la siguiente forma:

![imagenes-2](images/execute.png)

### 2.5. Resultados

Archivo de 10000 numeros antes de merge sort

![imagenes-3](images/input.png)

Archivo de 10000 numeros despues de merge sort

![imagenes-4](images/output.png)

### 2.6. Eficiencia

Los siguientes fueron los resultados para los datasets con N (número de datos) 100, 1000, 10000, 100000, 10000000.

- N = 100
  ![imagenes-5](images/time_100.png)

- N = 1000
  ![imagenes-6](images/time_1000.png)

- N = 10000
  ![imagenes-7](images/time_10000.png)

- N = 100000
  ![imagenes-8](images/time_100000.png)

- N = 1000000
  ![imagenes-9](images/time_1000000.png)

## 3. Algoritmo MPI

## 4. Algoritmo OpenMP
