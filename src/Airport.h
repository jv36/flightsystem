#ifndef FLIGHTSYSTEM_AIRPORT_H
#define FLIGHTSYSTEM_AIRPORT_H


#include <string>
#include <vector>
#include <queue>
#include <stack>
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


private:
    std::string code;
    std::string name;
    std::string city;
    std::string country;
    Location location;
};

#endif //FLIGHTSYSTEM_AIRPORT_H
