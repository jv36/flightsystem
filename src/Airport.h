//
// Created by joaomendes on 01-12-2023.
//

#ifndef FLIGHTSYSTEM_AIRPORT_H
#define FLIGHTSYSTEM_AIRPORT_H


#include <string>
#include <vector>
#include <queue>
#include "Location.h"
#include "Flight.h"
#include "Airline.h"

class Airport {
public:
    Airport(std::string code);
    Airport(std::string code, std::string name, std::string city, std::string country, Location location);
    std::string getCode() const;
    std::string getName() const;
    std::string getCity() const;
    std::string getCountry() const;
    Location getLocation() const;

    static void parseAirport();


private:
    std::string code;
    std::string name;
    std::string city;
    std::string country;
    Location location;
    float latitude;
    float longitude;
    std::vector<Airport>* airports;
};


#endif //FLIGHTSYSTEM_AIRPORT_H
