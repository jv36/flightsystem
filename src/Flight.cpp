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

std::string Flight::getSource() const {
    return source;
}

std::string Flight::getTarget() const {
    return target;
}
std::string Flight::getAirline() const {
    return airline;
}
//---- aux --- //
float toRadians(float degree) {
    return degree * (M_PI / 180.0);
}

float Flight::getDistance(Location source, Location dest) {

    const float EARTH_RADIUS = 6371.0;
    float sc_lat = toRadians(source.getLatitude());
    float dest_lat = toRadians(dest.getLatitude());

    float dLat = toRadians(dest.getLatitude()) - toRadians(source.getLatitude());
    float dLon = toRadians(dest.getLongitude()) - toRadians(source.getLongitude());

    float a = sin(dLat / 2) * sin(dLat / 2) +
              cos(sc_lat) * cos(dest_lat) *
              sin(dLon / 2) * sin(dLon / 2);
    float c = 2 * atan2(sqrt(a), sqrt(1 - a));

    float distance = EARTH_RADIUS * c;

    return distance;
}

/*void Flight::addAirline(std::string airlineCode) {
    this->airlines.push_back(airlineCode);
}*/

