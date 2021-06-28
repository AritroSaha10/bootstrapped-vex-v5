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
    // Set voltage of all motors to speed
    this->tLeft->move(speed);
    this->tRight->move(speed);
    this->bLeft->move(speed);
    this->bRight->move(speed);
}

void SkidSteerDrive::rotate(double speed) {
    // Run left motors at positive speed
    this->tLeft->move(speed);
    this->bLeft->move(speed);

    // Run right motors at negative speed
    this->tRight->move(-speed);
    this->bRight->move(-speed);
}

void SkidSteerDrive::stop() {
    // Set voltage of all motors to 0
    this->tLeft->move(0);
    this->tRight->move(0);
    this->bLeft->move(0);
    this->bRight->move(0);
}

void SkidSteerDrive::tank(double leftSpeed, double rightSpeed, double threshold) {
    // Apply threshold
    if (leftSpeed < threshold) {
        leftSpeed = 0;
    }

    if (rightSpeed < threshold) {
        rightSpeed = 0;
    }

    // Apply left speed to left motors
    this->tLeft->move(leftSpeed);
    this->bLeft->move(leftSpeed);

    // Apply right speed to right motors
    this->tRight->move(rightSpeed);
    this->bRight->move(rightSpeed);
}

void SkidSteerDrive::arcade(double forwardSpeed, double yaw, double threshold) {
    // Apply threshold
    if (forwardSpeed < threshold) {
        forwardSpeed = 0;
    }

    if (yaw < threshold) {
        yaw = 0;
    }

    // Apply power + turn to left side
    this->tLeft->move(forwardSpeed + yaw);
    this->bLeft->move(forwardSpeed + yaw);
    
    // Apply power - turn to right side
    this->tRight->move(forwardSpeed - yaw);
    this->bRight->move(forwardSpeed - yaw);
}