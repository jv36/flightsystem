//
// Created by joaomendes on 01-12-2023.
//

#ifndef FLIGHTSYSTEM_AIRPORT_H
#define FLIGHTSYSTEM_AIRPORT_H


#include <string>
#include <vector>
#include "Location.h"
#include "Flight.h"
#include "Airline.h"

class Airport {
public:
    Airport();
    Airport(std::string code, std::string name, std::string city, std::string country, Location location);

    std::string getCode() const;
    std::string getName() const;
    std::string getCity() const;
    std::string getCountry() const;
    Location getLocation() const;
    std::vector<Flight*> getFlights() const;
    std::vector<Airline*> getAirlines() const;

    void setCode(std::string code);
    void setName(std::string name);
    void setCity(std::string city);
    void setCountry(std::string country);
    void setLocation(Location location);
    void setFlights(std::vector<Flight*> flights);
    void setAirlines(std::vector<Airline*> airlines);
    void parseAirports(const std::string& filename,std::unordered_map<std::string, std::unique_ptr<Airport>>& airportMap);


private:
    std::string code;
    std::string name;
    std::string city;
    std::string country;
    Location location;
    std::vector<Flight*> flights;
    std::vector<Airline*> airlines;
};


#endif //FLIGHTSYSTEM_AIRPORT_H
