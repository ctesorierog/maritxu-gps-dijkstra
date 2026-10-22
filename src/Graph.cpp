#include "Graph.h"

Graph::Graph(int numNodos,int numAristas) : N(numNodos), M(numAristas) {
    adj.resize(N);      // Crear N listas vacías
    nombres.resize(N);  // Reservar espacio para N nombres
}

void Graph::agregarNombre(int id, const std::string& nombre) {
    nombres[id] = nombre;
}

void Graph::agregarArista(int origen, int destino, int peso) {
    // IMPORTANTE: Grafo NO DIRIGIDO
    // Añadir en AMBAS direcciones
    adj[origen].push_back({ destino, peso });
    adj[destino].push_back({ origen, peso });
    
}

std::string Graph::obtenerNombre(int id) const {
    return nombres[id];
}

#include <iostream>

/*void Graph::imprimir(std::vector<std::pair<int, int>>& consultas) const {

    std::cout << "N:" << N << "\nM:" << M << std::endl;


    // TODO 1: Imprimir N y M
    // std::cout << "N = " << N << ", M = " << M << "\n";

    // TODO 2: Imprimir los nombres
    // std::cout << "--- Nombres ---\n";
    // recorre nombres con un for indexado y muestra: i << " -> " << nombres[i]

    std::cout << "Nombres: " << std::endl;

    for (const std::string s : nombres) {
        std::cout << s << std::endl;
    
    }
    // TODO 3: Imprimir la lista de adyacencia
    // std::cout << "--- Adyacencia ---\n";
    // Para cada nodo u en [0, N):
    //   imprime "u (nombre): "
    //   para cada (v, peso) en adj[u]:
    //     imprime " -> v(peso)"
    //   newline
    for (int i = 0; i < N; i++) {
        std::cout << i << " (" << nombres[i] << "):"; // muestra también el ID

        
        for (const auto& p : adj[i]) {           // structured binding + & sin copia
            std::cout << "  -> " << p.first << "(" << nombres[p.first] << ", peso " << p.second << ")";
        }
        std::cout << "\n";   // salto al final de cada nodo


    }

    std::cout << "\n--- Consultas (" << consultas.size() << ") ---\n";
    for (size_t i = 0; i < consultas.size(); ++i) {
        std::cout << i + 1 << ": " << consultas[i].first
            << " -> " << consultas[i].second << "\n";
    }
    // Pregunta para vosotros: ¿qué tamaño esperáis que tenga la suma total de
    // entradas en adj? Pista: el grafo es no dirigido, M = 7 en el ejemplo...
}
*/

std::pair<int, std::vector<int>>Graph::dijkstra(int origen, int destino) {

    if (origen == destino) {
        return { 0, {origen} };
    }
    std::priority_queue<std::pair<int, int>, std::vector<std::pair<int, int>>, std::greater<>> pq;
    const int INF = std::numeric_limits<int>::max();
    std::vector<int>  dist(N, INF);
    std::vector<int>  previo(N, -1);
    std::vector<bool> visitado(N, false);

    dist[origen]=0;
    pq.push({ 0,origen });

    while (!pq.empty()) {
        auto [d, nod] = pq.top();    // desempaqueta el pair en dos variables nombradas
        pq.pop();
        // ... usas u directamente como "nodo actual"
        if(visitado[nod]) continue;  
        visitado[nod] = true;
        
        for (std::pair<int, int>& p : adj[nod]) {
            
            if (dist[nod] + p.second < dist[p.first]) {
                dist[p.first] = dist[nod] + p.second;
                previo[p.first] = nod;
                pq.push({ dist[p.first], p.first });
            }
            
           
        } 
        
    }

    // 1. ¿Es alcanzable el destino?
    if (dist[destino] == INF) {
        return { INF, {} };
    }

    // 2. Reconstruir el camino siguiendo previo[] desde destino hacia atras
    std::vector<int> camino;
    int actual = destino;
    while (actual != -1) {
        camino.push_back(actual);
        actual = previo[actual];
    }
    std::reverse(camino.begin(), camino.end());

    // 3. Devolver coste y camino
    return { dist[destino], camino };


}
//Devolvemos (dist,camino)
