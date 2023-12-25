//
// Created by joaomendes on 01-12-2023.
//

#ifndef FLIGHTSYSTEM_FLIGHT_H
#define FLIGHTSYSTEM_FLIGHT_H


#include <string>
#include <vector>
#include <unordered_map>
#include "Location.h"


class Flight {
public:
    Flight();
    Flight(std::string source, std::string target, std::string airline); //distance?

    std::string getSource() const;
    std::string getTarget() const;
    static float getDistance(Location source, Location dest);
    std::string getAirline() const;

    static void parseFlights();


private:
    std::string source;
    std::string target;
    std::string airline;
    float distance;
};


#endif //FLIGHTSYSTEM_FLIGHT_H
