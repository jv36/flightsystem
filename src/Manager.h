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
    std::unordered_map<std::string, std::pair<std::string, std::string>> cities;
    std::vector<std::pair<std::string, Location>> airportLocations;
    Graph* flightGraph = new Graph(1, false);
public:
    void parseFlights();
    void parseAirlines();
    void parseAirport();

    void printflightGraph();

    std::unordered_map<std::string, Airline*> getAirlines();
    std::unordered_map<std::string, Airport*> getAirports();

    // Airport menu
    unsigned long flightsFromAirport(const std::string& code);
    unsigned long airlinesFromAirport(const std::string &code);
    void printAirlinesFromAirport(const std::string &code);

    unsigned long cityDestinations(const std::string &code);
    void printCityDestinations(const std::string &code, const char& type);

    unsigned long countryDestinations(const std::string &code);
    void printCountryDestinations(const std::string &code);

    // Statistics

    // Global Statistics
    unsigned long globalAirports();
    void printGlobalAirports(const char& type);
    int globalFlights = 0;

    unsigned long globalAirlines();

    void printGlobalAirlines();

    unsigned long airportDestinations(const std::string &code);

    void printAirportDestinations(const std::string &code, const char &type);
};

#endif //FLIGHTSYSTEM_MANAGER_H
