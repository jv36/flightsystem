//
// Created by joaomendes on 01-12-2023.
//

#include "Airline.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <unordered_map>

Airline::Airline(std::string code) : code(code){
}

Airline::Airline(std::string code, std::string name, std::string callsign, std::string country) :
    code(code), callsign(callsign), name(name), country(country){
}


std::string Airline::getCode() const {
    return code;
}

 std::string Airline::getName() const {
    return name;
}

 std::string Airline::getCallsign() const {
    return callsign;
}

std::string Airline::getCountry() const {
    return country;
}

