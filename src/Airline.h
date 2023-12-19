//
// Created by joaomendes on 01-12-2023.
//

#ifndef FLIGHTSYSTEM_AIRLINE_H
#define FLIGHTSYSTEM_AIRLINE_H


#include <string>
#include "Flight.h"

class Airline {
public:
    Airline();
    Airline(std::string code, std::string name, std::string callsign, std::string country);

    const std::string& getCode() const;
    const std::string& getName() const;
    const std::string& getCallsign() const;
    const std::string& getCountry() const;
    std::vector<Flight*> getFlights() const;
    std::vector<std::string> getAirports() const;

    void setCode(std::string code);
    void setName(std::string name);
    void setCallsign(std::string callsign);
    void setCountry(std::string country);
    void setFlights(std::vector<Flight*> flights);
    void setAirports(std::vector<std::string> airports);
    void parseAirlines(const std::string& filename, std::unordered_map<std::string, std::unique_ptr<Airline>>& airportMap);


        private:
    std::string code;
    std::string name;
    std::string callsign;
    std::string country;
    std::vector<Flight*> flights;
    std::vector<std::string> airports;

};


#endif //FLIGHTSYSTEM_AIRLINE_H
