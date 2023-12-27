#include "Location.h"

Location::Location() {
    this->latitude = 0.0;
    this->longitude = 0.0;
}

Location::Location(float latitude, float longitude) {
    this->latitude = latitude;
    this->longitude = longitude;
}

float Location::getLatitude() const {
    return latitude;
}

float Location::getLongitude() const {
    return longitude;
}
