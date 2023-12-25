//
// Created by joaomendes on 01-12-2023.
//

#ifndef FLIGHTSYSTEM_MANAGER_H
#define FLIGHTSYSTEM_MANAGER_H

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <unordered_map>
#include "Graph.h"
class Manager {
    Graph createAirTravelGraph(const std::unordered_map<std::string, Graph::Node>& airports,
                         const std::vector<Graph::Edge>& flights);

};


#endif //FLIGHTSYSTEM_MANAGER_H
