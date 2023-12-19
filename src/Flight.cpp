//
// Created by joaomendes on 01-12-2023.
//

#include "Flight.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <unordered_map>

Flight::Flight() {
    this->source = "";
    this->target = "";
    this->airline = "";
    //this->distance = 0.0;
}

Flight::Flight(std::string source, std::string target, std::string airline) {
    this->source = source;
    this->target = target;
    this->airline = airline;
    //this->distance = distance;
}

const std::string &Flight::getSource() const {
    return source;
}

const std::string &Flight::getTarget() const {
    return target;
}
const std::string Flight::getAirline() const {
    return airline;
}

float Flight::getDistance() const {
    return distance;
}

const std::vector<std::string> &Flight::getAirlines() const {
    return airlines;
}

void Flight::setSource(const std::string &source) {
    this->source = source;
}

void Flight::setTarget(const std::string &target) {
    this->target = target;
}

void Flight::setDistance(float distance) {
    this->distance = distance;
}

void Flight::addAirline(std::string airlineCode) {
    this->airlines.push_back(airlineCode);
}

void Flight::parseFlights(const std::string& filename, std::unordered_map<std::string, std::unique_ptr<Flight>>& flightMap) {
    //alterar para o vosso absolute path ou alterar método
    std::ifstream file("/Users/claras/Desktop/flightsystem/csv/flights.csv");

    if (!file.is_open()) {
        std::cerr << "Error opening file!" << std::endl;
    }
    std::string line;

    //Source,Target,Airline
    getline(file, line);
    while (getline(file, line)) {
        std::istringstream iss(line);
        std::string source, target, airline;

        getline(iss, source, ',');
        getline(iss, target, ',');
        getline(iss, airline, ',');

        auto flight = std::make_unique<Flight>(source, target, airline);
        //flightMap[source] = std::move(flight);
    }
}
