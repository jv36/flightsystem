//
// Created by joaovicente on 18-12-2023.
//

#include <iostream>
#include "Graph.h"

Graph::Graph(){
    this->g_size = 0;
    this->dir = true;
}

int Graph::addAirport(Airport a){
    if(this->nodes.find(a.getCode())==this->nodes.end()) this->nodes.insert(std::pair<std::string,Node>(a.getCode(),{}));
    return this->nodes.size();
}

bool Graph::addFlight(std::string source, std::string dest, std::string airline) {
    return this->addFlight(source,dest,airline);
}

/*void Graph::printGraph() {
    for (const auto& node : nodes) {
        std::cout << "Airport: " << node.airport->getName() << "\nEdges:\n";
        for (const auto& edge : node.adj) {
            std::cout << "  To: " << edge.destAirport->getName() << ", Airline: " << edge.airline->getName() << ", Distance: " << edge.distance << "\n";
        }
        std::cout << "\n";
    }
}*/

