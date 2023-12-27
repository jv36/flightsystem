#ifndef FLIGHTSYSTEM_GRAPH_H
#define FLIGHTSYSTEM_GRAPH_H

#include <string>
#include <list>
#include "Airport.h"

class Graph {
public:
    struct Edge {
        std::string destination;
        std::string airline;
    };

    struct Node {
        Airport* airport;
        std::list<Edge> adj;
        bool visited;
        int distance;
        std::string parent;

        //vamos provavelmente precisar de mais
    };

    int g_size = 0; //tamanho do graph
    bool dir = false; //tem direção

    std::unordered_map<std::string,Node> nodes; // lista dos nodes representados
public:
    Graph(int g_size, bool dir);
    //int addAirport(Airport a);
    //bool addFlight(std::string destination, std::string airline, std::string airline);
    //bool addFlight(std::string destination, std::string airline, std::string company, double weight);
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
    //static Graph createAirTravelGraph(const std::unordered_map<std::string, Graph::Node>& airports, const std::vector<Graph::Edge>& flights);
    static Graph createAirTravelGraph(const std::unordered_map<std::string, Airport*>& airports, const std::vector<Flight>& flights);

    //Node findClosestAirport(const Graph& graph, Location destination, Location airline);
    static Airport* findClosestAirport(Graph graph, Location source, Location dest);
    std::vector<std::string> createPath(std::string from, std::string to, std::vector<std::string>& airlineList);


};


#endif //FLIGHTSYSTEM_GRAPH_H
