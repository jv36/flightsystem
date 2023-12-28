#include "Airport.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <unordered_map>

Airport::Airport(std::string code) : code(code){
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
