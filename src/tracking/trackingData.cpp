#include "tracking.h"

TrackingData::TrackingData(double x, double y, double h) {
    this->heading = h;
}

double TrackingData::getHeading() {
    return this->heading;
}

Vector2 TrackingData::getPos() {
    return this->pos;
}

Vector2 TrackingData::getForward() {
    return toGlobalCoordinates(Vector2(0, 1));
}

void TrackingData::update(double newX, double newY, double newH) {
    this->pos = Vector2(newX, newY);
    this->heading = newH;
}

void TrackingData::update(Vector2 newPos, double newH) {
    this->pos = newPos;
    this->heading = newH;
}