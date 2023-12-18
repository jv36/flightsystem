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
        std::string dest;
        std::string airport;
    };

    struct Node {
        Airport* airport;
        std::list<Edge> adj;
        bool visited;
        int distance;
        // precisa de mais
    };

public:
    Graph();
    void addNode();
    void addEdge();
    void setUnvisited();

};


#endif //FLIGHTSYSTEM_GRAPH_H
