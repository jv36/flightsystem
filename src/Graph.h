//
// Created by joaovicente on 18-12-2023.
//

#ifndef FLIGHTSYSTEM_GRAPH_H
#define FLIGHTSYSTEM_GRAPH_H


#include <string>
#include <list>
#include "Airport.h"

class Graph {
    struct Edge {
        std::string source; //de onde vem o avião
        std::string dest; // para onde vai o avião
        float w; //é weight mas n sei se será necessário
    };

    struct Node {
        std::list<Edge> adj;
        bool visited;

        //vamos provavelmente precisar de mais
    };

    int g_size = 0; //tamanho do gráfico
    bool dir = true; //tem direção

    std::unordered_map<std::string,Node> nodes; // lista dos nodes representados
public:
    Graph();
    int addAirport(Airport a);
    bool addFlight(std::string source, std::string dest, std::string airline);
    //bool addFlight(std::string source, std::string dest, std::string company, double weight);

    //void removeVisited();

    std::unordered_map<std::string,Node> getNodes(){
        return this->nodes;
    }

    //std::list<std::string> bfs(std::string in, std::string out);
    //std::pair<std::list<std::string>,double> djikstra(std::string in, std::string out);
    void printGraph(); // Helper function -> talvez mudar para main/menu no futuro
};


#endif //FLIGHTSYSTEM_GRAPH_H
