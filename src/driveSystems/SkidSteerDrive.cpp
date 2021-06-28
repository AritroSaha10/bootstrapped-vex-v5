#include "main.h"
#include "driveSystems/SkidSteerDrive.h"
#include "control/PID.h"
#include "tracking.h"

SkidSteerDrive::SkidSteerDrive(pros::Motor *tLeft, pros::Motor *tRight, pros::Motor *bLeft, pros::Motor *bRight) {
    this->tLeft = tLeft;
    this->tRight = tRight;
    this->bLeft = bLeft;
    this->bRight = bRight;
}

void SkidSteerDrive::move(double feet) {
    // ...
}

void SkidSteerDrive::moveTo(double x, double y) {
    // ...
}

void SkidSteerDrive::rotate(double degrees) {
    // ...
}

void SkidSteerDrive::rotateTo(double degrees) {
    // ...
}


