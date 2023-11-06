# PASOS PARA EJECUTAR FxC-EXP-Rendimiento

1- Ve a la carpeta MatMult y ejecuta el siguiente comando para compilar el programa MM1c usando el Makefile:
```console
make
```

2- Ve a la carpeta TOOL y asegurate que el script lanzador.pl y el archivo binario sea ejecutable (si aún no lo es) con el comando:
```console
chmod +x /home/s_rojas/project/FxC-EXP-Rendimiento/TOOL/lanzador.pl && \
chmod +x /home/s_rojas/project/FxC-EXP-Rendimiento/BIN/MM1c

chmod +x /home/s_rojas/project/FxF-EXP-Rendimiento/TOOL/lanzador.pl && \
chmod +x /home/s_rojas/project/FxF-EXP-Rendimiento/BIN/MM1f

chmod +x /home/s_rojas/project/FxC-EXP-Rendimiento-MPI/TOOL/lanzador.pl && \
chmod +x /home/s_rojas/project/FxC-EXP-Rendimiento-MPI/BIN/MM1c

chmod +x /home/s_rojas/project/FxC-EXP-Rendimiento-MPI/TOOL/lanzador.pl && \
chmod +x /home/s_rojas/project/FxC-EXP-Rendimiento-MPI/BIN/MM1c
```
3- Ejecuta el lanzador con el siguiente comando:
```console
./lanzador.pl 30
```
4- Con esto, el script lanzador.pl ejecutará el programa MM1c 30 veces para cada combinación de tamaño de vector y número de cores especificados en el script. Los resultados de la ejecución se almacenarán en el directorio Soluciones, y los tiempos de ejecución se almacenarán en el directorio Tiempos.