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
    };

    int g_size = 0; //tamanho do graph
    bool dir = false; //tem direção

    std::unordered_map<std::string,Node> nodes; // lista dos nodes representados
public:
    Graph(int g_size, bool dir);
    void addNode(const std::string& airportCode, Airport* airport);
    void addEdge(const std::string& originAirport, const std::string& destAirport, const std::string& airline);
    void bfs(const std::string& airportCode);
    void bfsFilteredRestrict(const std::string &airportCode, std::vector<std::string> &filter);
    void bfsFilteredExclude(const std::string &airportCode, std::vector<std::string> &filter);
    void dfs(const std::string &airportCode, std::vector<std::string>& currentPath, std::pair<std::string, std::string>& maxStopsPair);
    Node& nodeAtKey(const std::string& key);
    void removeVisited();
    void removeDistance();

    void articulationDFS(Node& node, std::vector<Airport*> &points, std::stack<Node>& st, int index);




    // FLIGHT PATHS
    std::vector<std::string> createPath(std::string from, std::string to, std::vector<std::string>& filter, int type);
    void printPath(const std::vector<std::string>& path);
};


#endif //FLIGHTSYSTEM_GRAPH_H
