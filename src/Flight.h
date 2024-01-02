#ifndef FLIGHTSYSTEM_FLIGHT_H
#define FLIGHTSYSTEM_FLIGHT_H

#include <string>
#include <vector>
#include <unordered_map>
#include "Location.h"


class Flight {
public:
    Flight();
    Flight(std::string source, std::string target, std::string airline);

    std::string getSource() const;
    std::string getTarget() const;
    std::string getAirline() const;

private:
    std::string source;
    std::string target;
    std::string airline;
    float distance;
};

#endif //FLIGHTSYSTEM_FLIGHT_H
