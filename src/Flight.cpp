//
// Created by joaomendes on 01-12-2023.
//

#include "Flight.h"

Flight::Flight() {
    this->source = "";
    this->target = "";
    this->distance = 0.0;
}

Flight::Flight(std::string source, std::string target, float distance) {
    this->source = source;
    this->target = target;
    this->distance = distance;
}

const std::string &Flight::getSource() const {
    return source;
}

const std::string &Flight::getTarget() const {
    return target;
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
