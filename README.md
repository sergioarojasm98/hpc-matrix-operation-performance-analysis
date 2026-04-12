# hpc-matrix-operation-performance-analysis

Benchmarking matrix multiplication methods (row-by-column vs row-by-row) with OpenMP parallelization on multi-core systems.

## About

This project measures the performance of two matrix multiplication strategies parallelized with OpenMP, comparing speedup and efficiency across systems with 10, 20, and 40 cores. Experiments were executed on three platforms: a MacBook, the university "Sistemas" cluster, and the "Cratos" multi-GPU server. Built for the High-Performance Computing (HPC) course in the Electronics Engineering / MSc program at Pontificia Universidad Javeriana, Bogota.

The repository contains the C kernels, Perl launcher scripts for batch execution, Python analysis scripts, and over 1,500 raw benchmark result files with pre-generated CSV summaries and PDF plots.

## Stack

| Component | Detail |
|---|---|
| Kernel language | C with OpenMP |
| Batch launcher | Perl (`lanzador.pl`) |
| Analysis | Python (pandas, matplotlib) |
| Build | Makefile per experiment directory |
| Matrix sizes | 100x100 to 1,000x1,000 |
| Platforms | MacBook, Sistemas cluster, Cratos server |

## How to Build / Run

```bash
# Compile
cd FxC-EXP-Rendimiento@MacBook/MatMult
make all

# Run batch experiment (30 repetitions)
cd ../TOOL
chmod +x lanzador.pl
perl lanzador.pl 30

# Analyze results
cd ../../Data-Analytics/Scripts
python hpc_results.py
python hpc_metrics.py
python hpc_plots.py
```

> **Note:** Paths in the launcher scripts are hardcoded to `/home/s_rojas/project/`. Adjust them to your local checkout before running.

## License

MIT
