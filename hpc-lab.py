import os
import re
from collections import defaultdict

def obtener_tiempo_promedio(archivo):
    """Obtiene el tiempo promedio de ejecución desde un archivo .time."""
    with open(archivo, 'r') as f:
        tiempos = [float(re.search(r'(\d+\.\d+)elapsed', linea).group(1)) for linea in f if re.search(r'elapsed', linea)]
        return sum(tiempos) / len(tiempos) if tiempos else 0

def main(directorio):
    """Procesa los archivos .time en el directorio y calcula las métricas de rendimiento."""
    archivos = [f for f in os.listdir(directorio) if f.endswith('.time')]

    tiempos_promedio = defaultdict(dict)
    for archivo in archivos:
        size = re.search(r'Size(\d+)', archivo).group(1)
        core_count = int(re.search(r'core(\d+)', archivo).group(1))
        tiempos_promedio[size][core_count] = obtener_tiempo_promedio(os.path.join(directorio, archivo))

    for size, tiempos in tiempos_promedio.items():
        tiempo_base = tiempos[1]
        print(f"\nResultados para Size{size}:")
        for cores, tiempo in tiempos.items():
            speedup = tiempo_base / tiempo
            eficiencia = speedup / cores
            print(f'  Para {cores} cores: Speedup = {speedup:.2f}, Eficiencia = {eficiencia:.2f}')

if __name__ == "__main__":
    directorio = input("Introduce el directorio donde se encuentran los archivos .time: ")
    main(directorio)
