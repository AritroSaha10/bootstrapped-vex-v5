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

void SkidSteerDrive::forward(double speed) {
    // ...
}

void SkidSteerDrive::rotate(double speed) {
    // ...
}

void SkidSteerDrive::stop() {
    // ...
}

void SkidSteerDrive::tank(double leftSpeed, double rightSpeed, double threshold) {
    // ...
}

void SkidSteerDrive::arcade(double forwardSpeed, double yaw, double threshold) {
    // ...
}