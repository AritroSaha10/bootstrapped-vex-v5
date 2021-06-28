#include "PID.h"
#include <math.h>
#include "main.h"

#define DBL_MAX 1.7E308
#define SETTLE_DELAY 2000

PIDInfo::PIDInfo(double p, double i, double d) {
    // Set local variables to object vars
    this->p = p;
    this->i = i;
    this->d = d;
};


PIDController::PIDController(double target, PIDInfo constants, double tolerance, double integralTolerance) {
    // Set local variables to object vars
    this->target = target;
    this->lastError = DBL_MAX;
    this->constants = constants;
    this->tolerance = tolerance;
    this->integralTolerance = integralTolerance;
}

double PIDController::step(double newSense) {
    // Set new sense
    this->sense = newSense;

    // Get new error
    this->error = this->target - this->sense;

    // If on first iter, set last error to current error
    if (this->lastError == DBL_MAX) {
        this->lastError = this->error;
    }

    // Add integral to error since integral is sum of all errors
    this->integral += this->error;

    // Get derivative (will be 0 on first iter since same)
    this->derivative = this->error - this->lastError;

    // Set last error since we're done with last error calcs for now
    this->lastError = this->error;

    // Disable integral until it enters usuable range (surpasses threshold)
    if (this->error == 0 || abs(this->error) > this->integralTolerance) {
        this->integral = 0;
    }

    // Run PID calculation with gains
    this->speed = (this->constants.p * this->error) + (this->constants.i * integral) + (this->constants.d * derivative);

    // Start settling if error falls under tolerance
    if (abs(this->error) <= this->tolerance) {
        // Start timer if it wasn't already settling
        if (!this->settling) {
            this->settleStart = pros::millis();
        }
        
        // Set variables
        this->settling = true;
        this->speed = 0;

        // Consider controller settled after SETTLE_DELAY
        if (pros::millis() - this->settleStart > SETTLE_DELAY) {
            this->settled = true;
        }
    } else {
        this->settling = false;
        this->settled = false;
    }

    // Return calculated speed
    return this->speed;
}

void PIDController::reset() {
    this->sense = 0;
    this->target = 0;
    this->speed = 0;

    this->lastError = 0;
    this->error = 0;

    this->integral = 0;
    this->derivative = 0;
}

double PIDController::getError() {
    return this->error;
}

bool PIDController::isSettled() {
    return this->settled;
}