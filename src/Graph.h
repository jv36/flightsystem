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
        bool inStack;
        int num;
        int low;
        //vamos provavelmente precisar de mais
    };

    int g_size = 0; //tamanho do graph
    bool dir = false; //tem direção

    std::unordered_map<std::string,Node> nodes; // lista dos nodes representados
public:
    Graph(int g_size, bool dir);
    void addNode(const std::string& airportCode, Airport* airport);
    void addEdge(const std::string& originAirport, const std::string& destAirport, const std::string& airline);
    void bfs(const std::string& airportCode);
    void dfs(const std::string& airportCode);
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



    void articulationDFS(Node& node, std::vector<Airport*> &points, std::stack<Node>& st, int index);
};


#endif //FLIGHTSYSTEM_GRAPH_H
