#include "Location.h"
#include <cmath>

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

double Location::toRadians(double degrees) const {
    return degrees * M_PI / 180.0;
}

double Location::calculateDistance(const Location& other) const {
    // Haversine formula
    const double R = 6371.0; // Earth radius in kilometers

    double lat1 = toRadians(latitude);
    double lon1 = toRadians(longitude);
    double lat2 = toRadians(other.getLatitude());
    double lon2 = toRadians(other.getLongitude());

    double dlat = lat2 - lat1;
    double dlon = lon2 - lon1;

    double a = std::sin(dlat / 2.0) * std::sin(dlat / 2.0) +
               std::cos(lat1) * std::cos(lat2) *
               std::sin(dlon / 2.0) * std::sin(dlon / 2.0);

    double c = 2.0 * std::atan2(std::sqrt(a), std::sqrt(1.0 - a));

    return R * c; // em kms
}
