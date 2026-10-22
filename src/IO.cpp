#include "IO.h"


// IO.cpp
bool readfile(const std::string& filename,
    Graph& grafo,
    std::vector<std::pair<int, int>>& consultas,
    std::string& mensajeError) {

    std::ifstream file(filename);

    if (!file.is_open()) {
        mensajeError = "No se pudo abrir el archivo";
        return false;
    }

    // Leer N y M
    int N, M;
    file >> N >> M;

    // Crear grafo con N nodos
    grafo = Graph(N,M);

    // Leer nombres (N líneas)
    for (int i = 0; i < N; i++) {
        int id;
        std::string nombre;
        file >> id >> nombre;
        grafo.agregarNombre(id, nombre);
    }

    // Leer aristas (M líneas)
    for (int i = 0; i < M; i++) {
        int origen, destino, peso;
        file >> origen >> destino >> peso;

        //DETECTAR PESO NEGATIVO AQUÍ
        if (peso < 0) {
            // Construir mensaje de error
            mensajeError = "ERROR: El grafo contiene aristas con peso negativo. Dijkstra no es aplicable.\n";
            mensajeError += "Arista con peso negativo detectada: ";
            mensajeError += grafo.obtenerNombre(origen) + " -- ";
            mensajeError += grafo.obtenerNombre(destino);
            mensajeError += " (peso: " + std::to_string(peso) + ")";

            file.close();
            return false;  
        }

        // Solo agregamos si NO es negativo
        grafo.agregarArista(origen, destino, peso);
    }

    // Buscar la línea #CONSULTAS
    std::string linea;
    while (std::getline(file, linea)) {
        if (linea == "#CONSULTAS") {
            break;
        }
    }

    // Leer consultas (resto del archivo)
    int origen, destino;
    while (file >> origen >> destino) {
        consultas.push_back({ origen, destino });
    }

    file.close();
    return true;  
}