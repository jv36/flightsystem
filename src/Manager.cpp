//
// Created by joaomendes on 01-12-2023.
//

#include "Manager.h"
#include <memory>
#include <unordered_set>

void Manager::printGraph() {
    for (auto& node : flightGraph->nodes) {
        std::cout << node.first;
    }
}

void Manager::parseAirlines() {

    std::ifstream file("../csv/airlines.csv");

    if (!file.is_open()) {
        std::cerr << "Error opening file!" << std::endl;
        return;
    }
    std::string line;

    getline(file, line);
    while (getline(file, line)) {
        std::istringstream iss(line);
        std::string code, name, callsign, country;

        getline(iss, code, ',');
        getline(iss, name, ',');
        getline(iss, callsign, ',');
        getline(iss, country, ',');

        auto airline = new Airline(code, name, callsign, country);
        airlines.insert({code, airline});
    }

    // Teste print
    /*
    for (const auto& name : airlines) {
        std::cout << name.second->getName() << std::endl;
    }
    std::cout << "There are " << airlines.size() << " airlines in our database.";
     */
}

 void Manager::parseAirport() {
     std::ifstream file("../csv/airports.csv");

     if (!file.is_open()) {
         std::cerr << "Error opening file!" << std::endl;
         return;
     }

     std::string line;
     getline(file, line);

     while (getline(file, line)) {
         std::istringstream iss(line);
         std::string code, name, city, country, latitude, longitude;

         getline(iss, code, ',');
         getline(iss, name, ',');
         getline(iss, city, ',');
         getline(iss, country, ',');
         getline(iss, latitude, ',');
         getline(iss, longitude,',');
         Location location = Location(std::stof(latitude), std::stof(longitude));
         auto airport = new Airport(code, name, city, country, location);

         airports.insert({code, airport});
         airportLocations.emplace_back(code, location);
     }

     // teste print
     /*
     for (const auto& code : airports) {
         std::cout << code.second->getName() << std::endl;
     }

     std::cout << "There are " << airports.size() << " airports in our database.";
      */
}

void Manager::parseFlights() {
    std::ifstream file("../csv/flights.csv");

    if (!file.is_open()) {
        std::cerr << "Error opening file!" << std::endl;
    }
    std::string line;

    flightGraph = new Graph(airports.size(), false);

    for (auto & airport : airports) {
        flightGraph->addNode(airport.first, airport.second);
    }


    //Source,Target,Airline
    getline(file, line);
    while (getline(file, line)) {
        std::istringstream iss(line);
        std::string source, target, airline;

        getline(iss, source, ',');
        getline(iss, target, ',');
        getline(iss, airline, ',');
        flightGraph->addEdge(source, target, airline);
    }
}



