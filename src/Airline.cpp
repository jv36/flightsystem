//
// Created by joaomendes on 01-12-2023.
//

#include "Airline.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <unordered_map>

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

void Airline::parseAirlines(const std::string& filename, std::unordered_map<std::string, std::unique_ptr<Airline>>& airlineMap) {
    //alterar para o vosso absolute path ou alterar método
    std::ifstream file("/Users/claras/Desktop/flightsystem/csv/airlines.csv");

    if (!file.is_open()) {
        std::cerr << "Error opening file!" << std::endl;
    }
    std::string line;


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
}
