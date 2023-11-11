import matplotlib.pyplot as plt
import pandas as pd
import os


def generar_graficas(directorio, archivo_csv):
    datos = pd.read_csv(os.path.join(directorio, archivo_csv))
    datos_filtrados = datos[datos["TotalCores"] > 1]  # Filtra para TotalCores > 1

    # Speedup vs. TotalCores
    plt.figure(figsize=(10, 7))
    for size in sorted(datos_filtrados["MatrixSize"].unique()):
        subset = datos_filtrados[datos_filtrados["MatrixSize"] == size]
        plt.plot(
            subset["TotalCores"], subset["Speedup"], marker="o", label=f"Size {size}"
        )
    plt.xlabel("Total Cores")
    plt.ylabel("Speedup")
    plt.title("Speedup vs. Total Cores")
    plt.legend()
    plt.savefig(os.path.join(directorio, "Speedup_vs_TotalCores.pdf"), format="pdf")

    # Eficiencia vs. TotalCores
    plt.figure(figsize=(10, 8))
    for size in sorted(datos_filtrados["MatrixSize"].unique()):
        subset = datos_filtrados[datos_filtrados["MatrixSize"] == size]
        plt.plot(
            subset["TotalCores"], subset["Eficiencia"], marker="o", label=f"Size {size}"
        )
    plt.xlabel("Total Cores")
    plt.ylabel("Eficiencia")
    plt.title("Eficiencia vs. Total Cores")
    plt.legend()
    plt.savefig(os.path.join(directorio, "Eficiencia_vs_TotalCores.pdf"), format="pdf")

    # Tiempo vs. MatrixSize para diferentes TotalCores
    plt.figure(figsize=(10, 7))
    for cores in sorted(datos["TotalCores"].unique()):
        subset = datos[datos["TotalCores"] == cores]
        plt.plot(
            subset["MatrixSize"], subset["Time"], marker="o", label=f"Cores {cores}"
        )
    plt.xlabel("Matrix Size")
    plt.ylabel("Time (microseconds)")
    plt.title("Execution Time vs. Matrix Size for different Total Cores")
    # Ajustar los márgenes de la subtrama
    plt.subplots_adjust(
        top=0.92,  # Reduce el espacio superior si es necesario
        bottom=0.08,  # Aumenta si la leyenda necesita más espacio
        left=0.10,  # Ajusta según necesidad para el eje y
        right=0.65,  # Deja espacio para la leyenda a la derecha
    )
    # Colocar la leyenda debajo del gráfico con 5 columnas
    plt.legend(
        loc="upper center",
        bbox_to_anchor=(0.5, -0.1),
        ncol=5,
        fancybox=True,
        shadow=True,
    )

    # Ajustar los márgenes para acomodar la leyenda
    plt.tight_layout(rect=[0, 0, 1, 1])

    # Guardar la figura ajustada
    plt.savefig(os.path.join(directorio, "Time_vs_MatrixSize.pdf"), format="pdf")


# Solicita al usuario ingresar la ruta del directorio de archivos
directorio = input("Please enter the directory path where the files are located: ")
archivo_csv = "resultados_con_metricas.csv"


# Llama a la función para generar y guardar las gráficas
generar_graficas(directorio, archivo_csv)

print("All graphs have been generated and saved as .pdf in the directory provided.")
