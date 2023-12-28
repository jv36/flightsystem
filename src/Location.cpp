#include "Location.h"

Location::Location() {
    this->latitude = 0.0;
    this->longitude = 0.0;
}

Location::Location(double latitude, double longitude) {
    this->latitude = latitude;
    this->longitude = longitude;
}

double Location::getLatitude() const {
    return latitude;
}

double Location::getLongitude() const {
    return longitude;
}
