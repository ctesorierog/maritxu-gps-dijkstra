// Graph.h
#pragma once
#include <vector>
#include <string>
#include <utility>  // para pair
#include <iostream>
#include <queue>       // priority_queue
#include <limits>      // numeric_limits<int>::max() para el INF
#include <functional>  // std::greater
#include <algorithm>   // std::reverse para reconstruir el camino


class Graph {
private:
    int N;  // Número de nodos
    int M;  // Número de aristas

    // adj[u] = (v, peso)
    // Significa: hay una arista de u a v con coste "peso"
    std::vector<std::vector<std::pair<int, int>>> adj;
    std::vector<std::string> nombres;

public:
    // Constructor
    Graph(int numNodos, int numAristas);

    // Agregar un nombre a un nodo
    void agregarNombre(int id, const std::string& nombre);

    // Agregar una arista 
    void agregarArista(int origen, int destino, int peso);

    // Algoritmo de Dijkstra
    // Devuelve: {coste total, camino como vector de IDs}
    std::pair<int, std::vector<int>>dijkstra(int origen, int destino);

    // Obtener nombre de un nodo
    std::string obtenerNombre(int id) const;

    // Imprimir debug
    void imprimir(std::vector<std::pair<int, int>>& consultas) const;


};