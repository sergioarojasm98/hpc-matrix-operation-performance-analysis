# PASOS PARA EJECUTAR FxC-EXP-Rendimiento

1- Ve a la carpeta MatMult y ejecuta el siguiente comando para compilar el programa MM1c usando el Makefile:
```console
make all
```

2- Ve a la carpeta TOOL y asegurate que el script lanzador.pl y el archivo binario sea ejecutable (si aún no lo es) con el comando:
```console
chmod +x /home/s_rojas/project/FxC-EXP-Rendimiento/TOOL/lanzador.pl && \
chmod +x /home/s_rojas/project/FxC-EXP-Rendimiento/BIN/MM1c

chmod +x /home/s_rojas/project/FxF-EXP-Rendimiento/TOOL/lanzador.pl && \
chmod +x /home/s_rojas/project/FxF-EXP-Rendimiento/BIN/MM1f

chmod +x /home/s_rojas/project/FxC-EXP-Rendimiento-MPI/TOOL/lanzador.pl && \
chmod +x /home/s_rojas/project/FxC-EXP-Rendimiento-MPI/BIN/MM1c

chmod +x /home/s_rojas/project/FxF-EXP-Rendimiento-MPI/TOOL/lanzador.pl && \
chmod +x /home/s_rojas/project/FxF-EXP-Rendimiento-MPI/BIN/MM1c
```
3- Ejecuta el lanzador con el siguiente comando:
```console
./lanzador.pl 30
```
4- Con esto, el script lanzador.pl ejecutará el programa MM1c 30 veces para cada combinación de tamaño de vector y número de cores especificados en el script. Los resultados de la ejecución se almacenarán en el directorio Soluciones, y los tiempos de ejecución se almacenarán en el directorio Tiempos.

# COMANDO PARA SUBIR NUEVOS ARCHIVOS DE CRATOS A CONDOR

1- Desde Condor, vaciar el folder del proyecto:
```console
rm -rf /home/s_rojas/project/*
```
2- Desde Cratos, copiar todos los archivos actualizados del Repo:
```console
scp -r /home/srojas/HPC/* s_rojas@10.34.1.2:/home/s_rojas/project/
```

# COMANDO PARA SUBIR RESULTADOS DE CONDOR A CRATOS

1- Desde Cratos, vaciar el folder del proyecto:
```console
rm -rf /home/srojas/HPC/*
```
2- Desde Condor, copiar todos los archivos/resultados actualizados del cluster:
```console
scp -r /home/s_rojas/project/* srojas@10.34.1.43:/home/srojas/HPC/
```
# RUTAS DE CARPETAS SOLUCIONES EN MACBOOK
```console
/Users/Sergio/GitHub/HPC/FxC-EXP-Rendimiento@Cratos/Soluciones
/Users/Sergio/GitHub/HPC/FxC-EXP-Rendimiento@MacBook/Soluciones
/Users/Sergio/GitHub/HPC/FxC-EXP-Rendimiento@Sistemas/Soluciones
/Users/Sergio/GitHub/HPC/FxF-EXP-Rendimiento@Cratos/Soluciones
/Users/Sergio/GitHub/HPC/FxF-EXP-Rendimiento@MacBook/Soluciones
/Users/Sergio/GitHub/HPC/FxF-EXP-Rendimiento@Sistemas/Soluciones
```
# Como funciona MM1x.c

Este código implementa una multiplicación de matrices utilizando programación paralela con OpenMP. Incluye la inicialización de matrices en el hilo maestro y luego realiza la multiplicación de las matrices en paralelo, utilizando cada hilo para trabajar en una parte de la matriz. Utiliza las funciones definidas en sample.h y Otime.c para medir y registrar el rendimiento de cada hilo durante la operación, ofreciendo una visión detallada del tiempo de ejecución de cada parte del proceso paralelizado. La barrera de OpenMP asegura que todos los hilos comiencen la multiplicación solo después de que las matrices estén completamente inicializadas.

# Como funciona Otime.c

Este código es parte de una implementación que mide el rendimiento de los hilos en un entorno de programación paralela con OpenMP. Utiliza estructuras timeval para registrar el tiempo de inicio y finalización de operaciones en cada hilo. La finalidad principal es medir el tiempo que tardan los hilos en ejecutar secciones específicas del código, lo cual es crucial para la optimización y el análisis del rendimiento en aplicaciones paralelas. Las funciones proporcionan un marco para iniciar y detener el muestreo, configurar el número de hilos y mostrar los resultados de los tiempos de ejecución al finalizar el programa.

# Como funciona lanzador.pl

Este script en Perl está diseñado para automatizar la ejecución de experimentos computacionales, específicamente para diferentes configuraciones de un programa (en este caso, "MM1c"). Acepta un argumento que define el número de repeticiones de cada experimento y luego itera sobre una serie de configuraciones predefinidas, incluyendo el tamaño del vector y el número de cores. Para cada configuración, ejecuta el programa correspondiente varias veces y guarda los resultados en un archivo. El script también incluye una función de utilidad (usage) para informar al usuario sobre el uso correcto en caso de que los argumentos de entrada no sean proporcionados adecuadamente.
