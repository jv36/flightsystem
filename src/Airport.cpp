//
// Created by joaomendes on 01-12-2023.
//

#include "Airport.h"

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
