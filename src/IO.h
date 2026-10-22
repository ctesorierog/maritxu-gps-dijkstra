#include <vector>
#include <string>
#include "Graph.h"
#include <fstream>
#include <iostream>

bool readfile(const std::string& filename,
    Graph& grafo,
    std::vector<std::pair<int, int>>& consultas,
    std::string& mensajeError);

