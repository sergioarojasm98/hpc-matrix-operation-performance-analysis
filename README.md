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

