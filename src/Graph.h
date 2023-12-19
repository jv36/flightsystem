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
        Airport* destAirport;
        Airline* airline;
        float distance;
    };

    struct Node {
        Airport* airport;
        std::list<Edge> adj;
        bool visited;
        float distance;
        //vamos provavelmente precisar de mais
    };

    std::vector<Node> nodes;

public:
    Graph();
    void addNode(Airport* airport);
    void addEdge(Airport* source, Airport* destination, Airline* airline, float distance);
    void setUnvisited();
    void printGraph(); // Helper function -> talvez mudar para main/menu no futuro
};


#endif //FLIGHTSYSTEM_GRAPH_H
