//
// Created by joaomendes on 01-12-2023.
//

#include "Manager.h"
#include <unordered_set>

/*void Graph::printGraph() {
    for (const auto &node: nodes) {
        std::cout << "Airport: " << node.airport->getName() << "\nEdges:\n";
        for (const auto &edge: node.adj) {
            std::cout << "  To: " << edge.destAirport->getName() << ", Airline: " << edge.airline->getName()
                      << ", Distance: " << edge.distance << "\n";
        }
        std::cout << "\n";
    }
}*/

void Airline::parseAirlines() {
    //alterar para o vosso absolute path ou alterar método
    std::ifstream file("/Users/claras/Desktop/flightsystem/csv/airlines.csv");

    if (!file.is_open()) {
        std::cerr << "Error opening file!" << std::endl;
    }
    std::string line;
    std::unordered_set<std::string> airlineNames;

    getline(file, line);
    while (getline(file, line)) {
        std::istringstream iss(line);
        std::string code, name, callsign, country;

        getline(iss, code, ',');
        getline(iss, name, ',');
        getline(iss, callsign, ',');
        getline(iss, country, ',');

        auto airline = std::make_unique<Airline>(code, name, callsign, country);
        airlineNames.insert(airline->getName());
    }
    for (const auto& name : airlineNames) {
        std::cout << name << std::endl;
    }
}

 void Airport::parseAirport() {
    /*const std::string &filename,
    std::unordered_map<std::string, std::vector<std::unique_ptr<Airport>>> &airportMap
    //alterar para o vosso absolute path ou alterar método*/

    /*std::ifstream file("/Users/claras/Desktop/flightsystem/csv/airports.csv");

    if (!file.is_open()) {
        std::cerr << "Error opening file!" << std::endl;
    }
    std::string line;


    getline(file, line);
    while (getline(file, line)) {
        std::istringstream iss(line);
        std::string code, name, city, country;
        double latitude, longitude;

        getline(iss, code, ',');
        getline(iss, name, ',');
        getline(iss, city, ',');
        getline(iss, country, ',');
        iss >> latitude >> longitude;

        auto airport = std::make_unique<Airport>(code, name, city, country, Location(latitude, longitude));
        if(airports->empty()){
            airports->emplace_back(airport->code);
        }else{
            for(auto it = airports->begin(); it != airports->end(); ++it){
                if(it->getCode() == airport->code){
                    continue;
                }else{
                    airports->emplace_back(airport->code);
                }
            }
        }
    }
    for(auto i: *airports){
        std::cout << i.getCode() << std::endl;
    }*/
     //este // é para mim
     // std::ifstream file("/csv/airports.csv");
     std::ifstream file("/Users/claras/Desktop/flightsystem/csv/airports.csv");

     if (!file.is_open()) {
         std::cerr << "Error opening file!" << std::endl;
         return;
     }

     std::string line;
     std::unordered_set<std::string> airportCodes;

     getline(file, line);

     while (getline(file, line)) {
         std::istringstream iss(line);
         std::string code, name, city, country;
         double latitude, longitude;

         getline(iss, code, ',');

         auto airport = std::make_unique<Airport>(code, name, city, country, Location(latitude, longitude));

         airportCodes.insert(airport->getCode());
     }

     for (const auto& code : airportCodes) {
         std::cout << code << std::endl;
     }
}

void Flight::parseFlights() {
    //alterar para o vosso absolute path ou alterar método
    std::ifstream file("/Users/claras/Desktop/flightsystem/csv/flights.csv");

    if (!file.is_open()) {
        std::cerr << "Error opening file!" << std::endl;
    }
    std::string line;

    std::unordered_map<std::string, std::vector<std::unique_ptr<Flight>>> flightMap;

    //Source,Target,Airline
    getline(file, line);
    while (getline(file, line)) {
        std::istringstream iss(line);
        std::string source, target, airline;

        getline(iss, source, ',');
        getline(iss, target, ',');
        getline(iss, airline, ',');

        auto flight = std::make_unique<Flight>(source, target, airline);
        flightMap[source].emplace_back(std::move(flight));
    }
}


