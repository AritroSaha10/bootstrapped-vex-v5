#include "main.h"
#include "driveSystems/tankdrive.h"

TankDrive::TankDrive(pros::Motor *tLeft, pros::Motor *tRight, pros::Motor *bLeft, pros::Motor *bRight) {
    this->tLeft = tLeft;
    this->tRight = tRight;
    this->bLeft = bLeft;
    this->bRight = bRight;
}

void TankDrive::move(double feet) {
    // ...
}

void TankDrive::moveTo(double x, double y) {
    // ...
}

void TankDrive::rotate(double degrees) {
    // ...
}

void TankDrive::rotateTo(double degrees) {
    // ...
}


