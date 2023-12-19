//
// Created by joaovicente on 18-12-2023.
//

#include <iostream>
#include "Graph.h"

void Graph::addNode(Airport* airport) {
    nodes.push_back({ airport, {}, false, 0.0 });
}

void Graph::addEdge(Airport* source, Airport* destination, Airline* airline, float distance) {
    for (auto& node : nodes) {
        if (node.airport == source) {
            node.adj.push_back({ destination, airline, distance });
            nodes.push_back({ destination, {}, false, 0.0 });
            nodes.back().adj.push_back({ source, airline, distance });
            break;
        }
    }
}

void Graph::setUnvisited() {
    for (auto& node : nodes) {
        node.visited = false;
    }
}

void Graph::printGraph() {
    for (const auto& node : nodes) {
        std::cout << "Airport: " << node.airport->getName() << "\nEdges:\n";
        for (const auto& edge : node.adj) {
            std::cout << "  To: " << edge.destAirport->getName() << ", Airline: " << edge.airline->getName() << ", Distance: " << edge.distance << "\n";
        }
        std::cout << "\n";
    }
}