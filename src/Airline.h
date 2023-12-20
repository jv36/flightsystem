//
// Created by joaomendes on 01-12-2023.
//

#ifndef FLIGHTSYSTEM_AIRLINE_H
#define FLIGHTSYSTEM_AIRLINE_H


#include <string>
#include "Flight.h"

class Airline {
public:
    Airline(std::string code);
    Airline(std::string code, std::string name, std::string callsign, std::string country);

    std::string getCode() const;
    std::string getName() const;
    std::string getCallsign() const;
    std::string getCountry() const;

    static void parseAirlines();

    bool operator==(const Airline& other);

    private:
    std::string code;
    std::string name;
    std::string callsign;
    std::string country;

    std::vector<Airline>* airlines;
};


#endif //FLIGHTSYSTEM_AIRLINE_H
