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
    std::unordered_map<std::string, unsigned long> flightsCity;
    std::unordered_map<std::string, unsigned long> flightsAirline;
    Graph* flightGraph = new Graph(1, false);
public:
    void parseFlights();
    void parseAirlines();
    void parseAirport();
    void printflightGraph();

    std::unordered_map<std::string, Airline*> getAirlines();
    std::unordered_map<std::string, Airport*> getAirports();

    void printArticulation(char type);

    // FLIGHTS
    void getFlightPath(std::string origin, std::string destination, int oType, int dType, std::vector<std::string>& filter, int type);



    // Filters

    bool validAirlineCode(const std::string& code);
    std::string getCodeFromName(const std::string& name);
    std::string getCodeFromCallsign(const std::string& callsign);
    std::vector<std::string> filterCountry(const std::string& country);


    // Airport menu
    unsigned long flightsFromAirport(const std::string& code);
    unsigned long airlinesFromAirport(const std::string &code);
    void printAirlinesFromAirport(const std::string &code);

    unsigned long cityDestinations(const std::string &code);
    void printCityDestinations(const std::string &code, const char& type);

    unsigned long countryDestinations(const std::string &code);
    void printCountryDestinations(const std::string &code);

    // Statistics
    void flightsPerCity(const std:: string& nameCity);

    void flightsPerAirline(const std:: string& nameAirline);

    void topKAirports(int k);


    // Global Statistics

    void directDestinations(const std::string& startAirport);

    void allDestinations(const std::string& startAirport);

    unsigned long globalAirports();

    void printGlobalAirports(const char& type);

    int globalFlights = 0;

    unsigned long globalAirlines();

    void printGlobalAirlines();

    unsigned long airportDestinations(const std::string &code);

    void printAirportDestinations(const std::string &code, const char &type);

    void destinationsWithinStops(const std::string& startAirport, int maxStops, bool type);
    void maximumTripWithStops();

    //void allDestinations(const std::string &startAirport);
    //void directDestinations(const std::string &startAirport);

    int graphDiameter();
};

#endif //FLIGHTSYSTEM_MANAGER_H
