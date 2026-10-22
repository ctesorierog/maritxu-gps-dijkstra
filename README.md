# Maritxu GPS: Dijkstra shortest paths in C++

A small route-planning engine for a road graph of Basque towns. It loads a weighted graph from a text file, answers a batch of shortest-path queries with Dijkstra's algorithm, and writes the cost, the route and per-query timings to `resultados.txt`.

## What it does

- Reads an undirected weighted graph (towns as nodes, roads as edges) plus a list of queries from one file.
- Validates the input and **rejects graphs with negative weights**, naming the offending edge, since Dijkstra is not valid there.
- Runs Dijkstra with a binary heap (`std::priority_queue`) over an adjacency list, so each query runs in O((V + E) log V).
- Reconstructs the path and handles edge cases: no path (`INFINITO`) and origin equal to destination.
- Times data loading, each query and the whole run with `std::chrono`.

## Input format

```
N M                 # number of nodes and edges
0 Donostia          # N lines: id name
...
0 1 8               # M lines: origin destination weight
...
#CONSULTAS
0 5                 # one query per line: origin destination
```

## Build and run

```bash
g++ -std=c++17 -O2 -o maritxu src/*.cpp
./maritxu data/small_graph.txt        # writes resultados.txt
```

## Example

`data/small_graph.txt` (6 towns, 7 roads) gives:

```
Consulta 1: Donostia -> Ordizia
Coste: 33
Camino: Donostia -> Hernani -> Tolosa -> Beasain -> Ordizia
```

Expected outputs for every sample are in `examples/`:

| Input | What it tests |
|---|---|
| `small_graph.txt` | Normal queries, including origin = destination |
| `negative_weight.txt` | Rejection of a negative edge |
| `large_500_nodes_negative.txt` | 500 nodes / 1,202 edges with one deliberately negative edge |

## Project structure

```
src/Graph.h, Graph.cpp   graph (adjacency list) + Dijkstra
src/IO.h, IO.cpp         file parsing and validation
src/main.cpp             query loop, output and timing
```

## Stack

C++17, STL (`vector`, `priority_queue`, `pair`), `chrono`. Originally built in Visual Studio.

## Credits

Group project for *Estructuras de Datos y Algoritmos*, AI Engineering, Tecnun (Universidad de Navarra), spring 2026.
