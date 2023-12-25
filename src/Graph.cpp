//
// Created by joaovicente on 18-12-2023.
//

#include <iostream>
#include "Graph.h"

Graph::Graph(){
    this->g_size = 0;
    this->dir = true;
}

void Graph::addNode(const std::string& airportCode, Airport* airport) {
    Node newNode;
    newNode.airport = airport;
    newNode.visited = false;
    newNode.distance = 0;
    newNode.parent = "";
    nodes.insert({airportCode, newNode});
}

void Graph::addEdge(const std::string &originAirport, const std::string &destAirport, const std::string &airline) {
    auto it = nodes.find(originAirport);
    auto it2 = nodes.find(destAirport);

    if (it == nodes.end() || it2 == nodes.end()) return;

    it->second.adj.push_back({originAirport, airline});
    if (!this->dir) it2->second.adj.push_back({originAirport, airline});

}

void Graph::bfs(const std::string &airportCode) {
    this->removeDistance();
    this->removeVisited();

    std::queue<std::string> q;
    q.push(airportCode);
    nodes[airportCode].visited = true;
    nodes[airportCode].distance = 0;

    // while unvisited
    while (!q.empty()) {
        std::string top = q.front();
        q.pop();

        for (const Edge& e : nodes.at(top).adj) {
            if (!nodes[e.dest].visited) {
                q.push(e.dest);
                nodes[e.dest].visited = true;
                nodes[e.dest].parent = top;
                nodes[e.dest].distance = nodes[top].distance + 1;
            }
        }
    }

}

Graph::Node &Graph::nodeAtKey(const std::string &key) {
    Node& node = this->nodes[key];
    return node;
}

void Graph::removeVisited() {
    for (auto& node: nodes) {
        node.second.visited = false;
    }
}

void Graph::removeDistance() {
    for (auto& node: nodes) {
        node.second.distance = -1;
    }
}
void Graph::clearGraph() {
    this->nodes.clear();
}

int Graph::distance(const std::string& in, const std::string& out) {
    if (in == out) {
        return 0;
    }
    bfs(in);
    int dist = nodes[out].distance;
    return dist;
}

std::vector<std::string> Graph::createPath(std::string from, std::string to, std::vector<std::string> &airlineList) {
    // tem de se filtrar depois faço

    return std::vector<std::string>();
}

/*
int Graph::addAirport(Airport a){
    if(this->nodes.find(a.getCode())==this->nodes.end()) this->nodes.insert(std::pair<std::string,Node>(a.getCode(),{}));
    return this->nodes.size();
}

bool Graph::addFlight(std::string source, std::string dest, std::string airline) {
    return this->addFlight(source,dest,airline);
}

void Graph::printGraph() {
    for (const auto& node : nodes) {
        std::cout << "Airport: " << node.airport->getName() << "\nEdges:\n";
        for (const auto& edge : node.adj) {
            std::cout << "  To: " << edge.destAirport->getName() << ", Airline: " << edge.airline->getName() << ", Distance: " << edge.distance << "\n";
        }
        std::cout << "\n";
    }
}*/
Airport* Graph::findClosestAirport(const Graph& graph, Location source, Location dest) {
    Airport* closestAirport;
    double minDistance = std::numeric_limits<double>::infinity();

    for (const auto& nodePair : graph.nodes) {
        const Node& node = nodePair.second;
        double distance = Flight::getDistance(source, dest);

        if (distance < minDistance) {
            minDistance = distance;
            closestAirport = node.airport;
        }
    }

    return closestAirport;
}


