import csv
import os
from collections import defaultdict


# Función para calcular el promedio de los promedios y las métricas de rendimiento
def calcular_metricas(tiempos_base, datos):
    resultados_con_metricas = []
    for matrix_size, datos_cores in datos.items():
        for cores, tiempos in datos_cores.items():
            promedio = sum(tiempos) / len(tiempos)
            speedup = tiempos_base[matrix_size] / promedio
            eficiencia = speedup / int(cores)
            resultados_con_metricas.append(
                {
                    "TotalCores": cores,
                    "MatrixSize": matrix_size,
                    "Time": promedio,
                    "Speedup": speedup,
                    "Eficiencia": eficiencia,
                }
            )
    return resultados_con_metricas


# Solicita al usuario ingresar la ruta del directorio de archivos
directorio = input("Ingresa la ruta del directorio donde se encuentran los archivos: ")

# Verifica si el directorio existe
if not os.path.exists(directorio):
    print(f"El directorio '{directorio}' no existe.")
    exit()

# Diccionarios para almacenar los tiempos
tiempos_base = {}
datos_agrupados = defaultdict(lambda: defaultdict(list))

# Leer el archivo de resultados existente para obtener los tiempos
with open(os.path.join(directorio, "resultados.csv"), mode="r") as archivo_base:
    lector_csv = csv.DictReader(archivo_base)
    for fila in lector_csv:
        cores = fila["TotalCores"]
        matrix_size = fila["MatrixSize"]
        tiempo = float(fila["Time"])
        datos_agrupados[matrix_size][cores].append(tiempo)
        if cores == "1":  # Guardamos el tiempo base para 1 core
            tiempos_base[matrix_size] = tiempo

# Calcula las métricas de rendimiento
resultados_con_metricas = calcular_metricas(tiempos_base, datos_agrupados)

# Ordena los datos por TotalCores y luego por MatrixSize
resultados_con_metricas.sort(key=lambda x: (int(x["TotalCores"]), int(x["MatrixSize"])))

# Ruta donde se guardará el archivo CSV con métricas
ruta_csv = os.path.join(directorio, "resultados_con_metricas.csv")

# Escribe los datos en un archivo CSV en la misma ruta de entrada
with open(ruta_csv, mode="w", newline="") as archivo_csv:
    campos = ["TotalCores", "MatrixSize", "Time", "Speedup", "Eficiencia"]
    escritor_csv = csv.DictWriter(archivo_csv, fieldnames=campos)

    # Escribe el encabezado
    escritor_csv.writeheader()

    # Escribe las filas de datos
    for fila in resultados_con_metricas:
        escritor_csv.writerow(fila)

print(f"Los datos con métricas se han guardado en '{ruta_csv}'.")
