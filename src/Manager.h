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
#include <memory>
#include <unordered_set>
#include "Graph.h"
class Manager {
private:
    std::unordered_map<std::string, std::vector<std::unique_ptr<Flight>>> flightMap;
    std::unordered_map<std::string, Airline*> airlines;
    std::unordered_map<std::string, Airport*> airports;
    std::vector<std::pair<std::string, Location>> airportLocations;
    Graph* flightGraph = new Graph(1, false);
public:
    void parseFlights();
    void parseAirlines();

    void parseAirport();

    void printGraph();
};


#endif //FLIGHTSYSTEM_MANAGER_H
