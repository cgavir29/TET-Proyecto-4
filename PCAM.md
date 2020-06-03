# PCAM

![](https://i.imgur.com/sNxCkzn.png)

## 1. Problema
Merge Sort es un algoritmo basado en Divide y Conquista. Divide la matriz de entrada en dos mitades, se llama a sí misma para las dos mitades y luego combina las dos mitades ordenadas. La función merge() se usa para fusionar dos mitades. La combinación (arr, l, m, r) es un proceso clave que supone que arr [l..m] y arr [m + 1..r] se ordenan y fusiona las dos sub-arreglos ordenadas en una.
 
Nuestro objetivo es ejecutar el algoritmo anterior de forma paralela utilizando la metodología PCAM para el análisis e implemetación.

![](https://i.imgur.com/AHi2gfu.png)

## 2. Particionamiento

En esta sección, después de leer el fichero `.txt` donde se encuentran los datos a ordenar pasamos a hacer una división de estos (en forma de arreglo) para después mediante el algoritmo distribuirlos entre los diferentes procesos.

![](https://i.imgur.com/3ZoNVAm.png)

## 3. Comunicación

Se determina la comunicación requerida para coordinar la ejecución de los procesos, y se definen la estructura del algoritmo a ejecutar. Esta comunicación se coordina a través de mensajes _MPI_Send(...)_ y _MPI_Recv(...)_.

![](https://i.imgur.com/OS65kR4.png)

## 4. Aglomeración

Se evaluan las etapas de particionamiento y comunicación, luego se determina si es posible mejorar el rendimiento o reducir los costos mediante la combinación de tareas.

![](https://i.imgur.com/W8yjLdP.png)

## 5. Mapeo

Como se observa en el artículo de Manwade, K. B. (2010) maximizar el número de procesadores no resula siempre en una mejora de rendimiento para un mismo tamaño de datos, lo cual indica que se debe tener un balance en entre la cantidad de datos que se maneja y el número de procesadores así como las tareas que se asignan a cada uno de estos. Dentro de nuestra ejecución una vez las tareas van terminando y llegan hasta el proceso raíz (el que se encarga de hacer la lectura y distribución inicial de los datos), estos se juntan en un solo arreglo el cual se escribe finalmente a un fichero `.txt` donde se plasman los resultados del ordenamiento usando el algoritmo _Merge Sort Paralelo_.

![](https://i.imgur.com/JHg0bMQ.png)

## 6. Referencias

[1] Manwade, K. B. (2010). Analysis of parallel merge sort algorithm.
International Journal of Computer Applications, 1(19), 66-69.

[2] Khan, H. U., &amp; Tiwari, R. (2012). An adaptive framework towards analyzing
the parallel merge sort. International Journal of Science and Research (IJSR), 1(2).

[3] https://www.mcs.anl.gov/~itf/dbpp/text/node15.html

[4] https://homepage.physics.uiowa.edu/~ghowes/teach/ihpc12/lec/ihpc12Lec_DesignHPC12.pdf
