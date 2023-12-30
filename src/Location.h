#ifndef FLIGHTSYSTEM_LOCATION_H
#define FLIGHTSYSTEM_LOCATION_H


class Location {
public:
    Location();
    Location(double latitude, double longitude);

    double getLatitude() const;
    double getLongitude() const;
public:
    double latitude;
    double longitude;

    double toRadians(double degrees) const;

    double calculateDistance(const Location &other) const;
};

#endif //FLIGHTSYSTEM_LOCATION_H
