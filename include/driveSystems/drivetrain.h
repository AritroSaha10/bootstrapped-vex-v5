/**
 * \file drivetrain.h
 * 
 * \brief Contains headers for the Drivetrain abstract class.
*/

#pragma once

#include "main.h"

/**
 * \brief Base class for different types of drivetrains, ex. holonomic, nonholonomic
*/
class Drivetrain {
    public:
        /**
         * Initializes the Drivetrain class
        */
        Drivetrain() {};

        /**
         * Drives chassis forward at specific speed
         * @param speed The speed in range [-127, 127]
        */ 
        virtual void forward(double speed) = 0;

        /**
         * Rotate chassis clockwise at specific speed
         * @param speed The speed in range [-127, 127]
        */ 
        virtual void rotate(double speed) = 0;

        /**
         * Stop providing power to motors
        */
        virtual void stop() = 0;

        /**
        * Drive robot in tank drive controller layout
        * @param leftSpeed Speed provided to left side of chassis, in range [-127, 127]
        * @param rightSpeed Speed provided to right side of chassis, in range [-127, 127]
        * @param threshold Threshold of value before rounding to 0
        */
        virtual void tank(double leftSpeed, double rightSpeed, double threshold = 0) = 0;

        /**
        * Drive robot in arcade drive controller layout
        * @param forwardSpeed Speed provided to move the chassis forward, in range [-127, 127]
        * @param yaw Speed provided to turn the chassis, in range [-127, 127]
        * @param threshold Threshold of value before rounding to 0
        */
        virtual void arcade(double forwardSpeed, double yaw, double threshold = 0) = 0;
};