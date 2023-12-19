//
// Created by joaomendes on 01-12-2023.
//

#include <cstdlib>
#include <iostream>
#include "Airport.h"
#include <unordered_map>
#include <fstream>
#include <sstream>

#include "Menu.h"
int Menu::main() {
    std::unordered_map<std::string, std::unique_ptr<Airline>> airlineMap;        /*std::ifstream file(filename);
        std::string line;

        std::getline(file, line); // Skip the header line

        while (std::getline(file, line)) {
            std::istringstream iss(line);
            std::string Code, Name, City, Country;
            double latitude, longitude;

            if (iss >> Code >> Name >> City >> Country >> latitude >> longitude) {
                auto airport = std::make_unique<Airport>(Code, Name, City, Country, Location(latitude, longitude));
                std::cout << "Airport address: " << airport.get() << std::endl;
                airportMap[Code] = std::move(airport);
            }
        }*/
        std::ifstream file("/Users/claras/Desktop/flightsystem/csv/airlines.csv");

    if (!file.is_open()) {
        std::cerr << "Error opening file!" << std::endl;
        return 1; // Return an error code
    }
        std::string line;

    //Code,Name,Callsign,Country

    getline(file, line);
    while (getline(file, line)) {
        std::istringstream iss(line);
        std::string code, name, callsign, country;

        getline(iss, code, ',');
        getline(iss, name, ',');
        getline(iss, callsign, ',');
        getline(iss, country, ',');

        auto airline = std::make_unique<Airline>(code, name, callsign, country);
        std::cout << airline->getName() << std::endl;
        airlineMap[code] = std::move(airline);
    }
    return 0;
}