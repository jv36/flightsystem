//
// Created by joaomendes on 01-12-2023.
//

#ifndef FLIGHTSYSTEM_LOCATION_H
#define FLIGHTSYSTEM_LOCATION_H


class Location {
public:
    Location();
    Location(float latitude, float longitude);

    float getLatitude() const;
    float getLongitude() const;
public:
    float latitude;
    float longitude;
};


#endif //FLIGHTSYSTEM_LOCATION_H
