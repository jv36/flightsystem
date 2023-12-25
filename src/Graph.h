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
        Airport* airport;
        std::list<Edge> adj;
        bool visited;
        int distance;
        std::string parent;

        //vamos provavelmente precisar de mais
    };

    int g_size = 0; //tamanho do gráfico
    bool dir; //tem direção

    std::unordered_map<std::string,Node> nodes; // lista dos nodes representados
public:
    Graph();
    //int addAirport(Airport a);
    //bool addFlight(std::string source, std::string dest, std::string airline);
    //bool addFlight(std::string source, std::string dest, std::string company, double weight);
    //void removeVisited();
    /*
    std::unordered_map<std::string,Node> getNodes(){
        return this->nodes;
    }

    //std::list<std::string> bfs(std::string in, std::string out);
    //std::pair<std::list<std::string>,double> djikstra(std::string in, std::string out);
    void printGraph(); // Helper function -> talvez mudar para main/menu no futuro
     */

    // Clara, deixa refazer isto:

    void addNode(const std::string& airportCode, Airport* airport);
    void addEdge(const std::string& originAirport, const std::string& destAirport, const std::string& airline);
    void bfs(const std::string& airportCode);
    Node& nodeAtKey(const std::string& key);
    void removeVisited();
    void removeDistance();
    void clearGraph();
    int distance(const std::string& in, const std::string& out);

    //Node findClosestAirport(const Graph& graph, Location source, Location dest);
    Airport* findClosestAirport(const Graph& graph, Location source, Location dest);
    std::vector<std::string> createPath(std::string from, std::string to, std::vector<std::string>& airlineList);


};


#endif //FLIGHTSYSTEM_GRAPH_H
