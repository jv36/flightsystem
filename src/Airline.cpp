//
// Created by joaomendes on 01-12-2023.
//

#include "Airline.h"

Airline::Airline() {
    this->code = "";
    this->name = "";
    this->callsign = "";
    this->country = "";
}

Airline::Airline(std::string code, std::string name, std::string callsign, std::string country) {
    this->code = code;
    this->name = name;
    this->callsign = callsign;
    this->country = country;
}

const std::string& Airline::getCode() const {
    return code;
}

const std::string& Airline::getName() const {
    return name;
}

const std::string& Airline::getCallsign() const {
    return callsign;
}

const std::string& Airline::getCountry() const {
    return country;
}

std::vector<Flight *> Airline::getFlights() const {
    return flights;
}

std::vector<std::string> Airline::getAirports() const {
    return airports;
}

void Airline::setCode(std::string code) {
    this->code = code;
}

void Airline::setName(std::string name) {
    this->name = name;
}

void Airline::setCallsign(std::string callsign) {
    this->callsign = callsign;
}

void Airline::setCountry(std::string country) {
    this->country = country;
}

void Airline::setFlights(std::vector<Flight *> flights) {
    this->flights = flights;
}

void Airline::setAirports(std::vector<std::string> airports) {
    this->airports = airports;
}
