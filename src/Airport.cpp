//
// Created by joaomendes on 01-12-2023.
//

#include "Airport.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <unordered_map>


Airport::Airport() {
    this->code = "";
    this->name = "";
    this->city = "";
    this->country = "";
    this->location = Location(0.0, 0.0);
}

Airport::Airport(std::string code, std::string name, std::string city, std::string country, Location location) {
    this->code = code;
    this->name = name;
    this->city = city;
    this->country = country;
    this->location = location;
}

std::string Airport::getCode() const {
    return code;
}

std::string Airport::getName() const {
    return name;
}

std::string Airport::getCity() const {
    return city;
}

std::string Airport::getCountry() const {
    return country;
}

Location Airport::getLocation() const {
    return location;
}

std::vector<Flight *> Airport::getFlights() const {
    return flights;
}

std::vector<Airline *> Airport::getAirlines() const {
    return airlines;
}

void Airport::setCode(std::string code) {
    this->code = code;
}

void Airport::setName(std::string name) {
    this->name = name;
}

void Airport::setCity(std::string city) {
    this->city = city;
}

void Airport::setCountry(std::string country) {
    this->country = country;
}

void Airport::setLocation(Location location) {
    this->location = location;
}

void Airport::setFlights(std::vector<Flight *> flights) {
    this->flights = flights;
}

void Airport::setAirlines(std::vector<Airline *> airlines) {
    this->airlines = airlines;
}

void Airport::parseAirports(const std::string& filename, std::unordered_map<std::string, std::unique_ptr<Airport>>& airportMap) {
    //alterar para o vosso absolute path ou alterar método

    std::ifstream file("/Users/claras/Desktop/flightsystem/csv/airports.csv");

    if (!file.is_open()) {
        std::cerr << "Error opening file!" << std::endl;
    }
    std::string line;


    getline(file, line);
    while (getline(file, line)) {
        std::istringstream iss(line);
        std::string code, name, city, country;
        double latitude, longitude;

        getline(iss, code, ',');
        getline(iss, name, ',');
        getline(iss, city, ',');
        getline(iss, country, ',');
        iss >> latitude >> longitude;

        auto airport = std::make_unique<Airport>(code, name, city, country, Location(latitude, longitude));
        airportMap[code] = std::move(airport);

    }
}
