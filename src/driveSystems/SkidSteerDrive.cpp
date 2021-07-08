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
    this->tLeft->move(speed);
    this->tRight->move(speed);
    this->bLeft->move(speed);
    this->bRight->move(speed);
}

void SkidSteerDrive::rotate(double speed) {
    this->tLeft->move(speed);
    this->bLeft->move(speed);

    this->tRight->move(-speed);
    this->bRight->move(-speed);
}

void SkidSteerDrive::stop() {
    this->tLeft->move(0);
    this->tRight->move(0);
    this->bLeft->move(0);
    this->bRight->move(0);
}

void SkidSteerDrive::tank(double leftSpeed, double rightSpeed, double threshold) {
    // Apply threshold
    leftSpeed = leftSpeed < threshold ? 0 : leftSpeed;
    rightSpeed = rightSpeed < threshold ? 0 : rightSpeed;

    this->tLeft->move(leftSpeed);
    this->bLeft->move(leftSpeed);

    this->tRight->move(rightSpeed);
    this->bRight->move(rightSpeed);
}

void SkidSteerDrive::arcade(double forwardSpeed, double yaw, double threshold) {
    // Apply threshold
    forwardSpeed = forwardSpeed < threshold ? 0 : forwardSpeed;
    yaw = forwardSpeed < threshold ? 0 : yaw;

    this->tLeft->move(forwardSpeed + yaw);
    this->bLeft->move(forwardSpeed + yaw);
    
    this->tRight->move(forwardSpeed - yaw);
    this->bRight->move(forwardSpeed - yaw);
}