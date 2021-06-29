#include "main.h"
#include "globals.h"

void myAuton() {
    driveTrainPID.moveToPoint(Vector2(1, 1)); // Go to 1ft x 1ft
    
    pros::delay(40);

    driveTrainPID.rotateTo(degToRad(90)); // Rotate to 90 degrees

    driveTrainPID.moveToOrientation(Vector2(10, 10), degToRad(95)); // Go to 10ft x 10ft and settle at a 95 degree rotation
}