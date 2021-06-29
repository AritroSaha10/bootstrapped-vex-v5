#include "tracking.h"
#include "globals.h"
#include <math.h>

double radToDeg(double r) {
    return r * 180./M_PI;
}

double degToRad(double d) {
    return d * M_PI/180.;
}

Vector2 rotateVector(Vector2 vec, double angle) {
    // x = cos(a), y = sin(a)
	// cos(a + b) = cos(a)cos(b) - sin(a)sin(b)
	double newX = (vec.getX() * cos(angle)) - (vec.getY() * sin(angle));

	// sin(a + b) = sin(a)cos(b) + cos(a)sin(b)
	double newY = (vec.getY() * cos(angle)) + (vec.getX() * sin(angle));

	return Vector2(newX, newY);
}

Vector2 toLocalCoordinates(Vector2 vec) {
    double localAngle = -trackingData.getHeading();

	return rotateVector(vec, localAngle);
}

Vector2 toGlobalCoordinates(Vector2 vec) {
    double localAngle = trackingData.getHeading();

	return rotateVector(vec, localAngle);
}