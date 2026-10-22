#include <iostream>
#include <fstream>
#include "IO.h"
#include "Graph.h"
#include <chrono>
#include <iomanip>

int main(int argc, char* argv[]) {
    auto t_inicio = std::chrono::high_resolution_clock::now();
    
    if (argc < 2) {
        std::cerr << "Usa: " << argv[0] << " grafo.txt\n";
        return 1;
    }

    std::string filename = argv[1];
    Graph grafo(0, 0);
    std::vector<std::pair<int, int>> consultas;
    std::string mensajeError;

    bool ok = readfile(filename, grafo, consultas, mensajeError);

    std::ofstream out("resultados.txt");
    if (!out.is_open()) {
        std::cerr << "No se pudo crear resultados.txt\n";
        return 1;
    }

    auto t_carga_fin = std::chrono::high_resolution_clock::now();
    double tiempo_carga_ms = std::chrono::duration<double, std::milli>(t_carga_fin - t_inicio).count();

    if (!ok) {
        out << mensajeError;
        return 0;
    }

    // Aquí va el bucle de consultas (siguiente paso)
    double tiempo_procesamiento_ms = 0.0;

    for (size_t i = 0; i < consultas.size(); ++i) {
        int origen = consultas[i].first;
        int destino = consultas[i].second;

        // Cronómetro individual de la consulta
        auto iniciot = std::chrono::high_resolution_clock::now();
        auto resultado = grafo.dijkstra(origen, destino);
        auto fint = std::chrono::high_resolution_clock::now();

        double tiempoMS = std::chrono::duration<double, std::milli>(fint - iniciot).count();
        tiempo_procesamiento_ms += tiempoMS;

        int coste = resultado.first;
        const std::vector<int>& camino = resultado.second;

        // Cabecera: "Consulta N: ORIGEN -> DESTINO"
        out << "Consulta " << (i + 1) << ": "
            << grafo.obtenerNombre(origen) << " -> "
            << grafo.obtenerNombre(destino) << "\n";

        // Coste y Camino (con casos especiales)
        if (camino.empty()) {
            // Caso: no existe camino
            out << "Coste: INFINITO\n";
            out << "Camino: SIN CAMINO\n";
        }
        else {
            // Caso normal (también incluye origen==destino, donde camino tiene 1 elemento)
            out << "Coste: " << coste << "\n";
            out << "Camino: ";
            for (int j = 0; j < camino.size(); j++) {
                out << grafo.obtenerNombre(camino[j]);
                if (j + 1 < camino.size()) out << " -> ";
            }
            out << "\n";
        }

        // Tiempo individual
        out << "Tiempo: " << std::fixed << std::setprecision(3)
            << tiempoMS << " ms\n";

        // Línea en blanco entre consultas (no después de la última)
        if (i + 1 < consultas.size()) {
            out << "\n";
        }
    }
    // Calcular el tiempo total (desde inicio hasta ahora)
    auto t_total_fin = std::chrono::high_resolution_clock::now();
    double tiempo_total_ms = std::chrono::duration<double, std::milli>(t_total_fin - t_inicio).count();

    // Escribir el bloque final de tiempos
    out << "\n---\n";
    out << "Tiempo de carga de datos: " << std::fixed << std::setprecision(3)
        << tiempo_carga_ms << " ms\n";
    out << "Tiempo de procesamiento de consultas: " << std::fixed << std::setprecision(3)
        << tiempo_procesamiento_ms << " ms\n";
    out << "Tiempo total: " << std::fixed << std::setprecision(3)
        << tiempo_total_ms << " ms\n";

    out.close();

    return 0;
}