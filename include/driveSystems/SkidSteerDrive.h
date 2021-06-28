#pragma once

#include "main.h"
#include "drivetrain.h"

/**
 * Class object to control a nonholomic / "tank drive" robot drivetrain
 * Utilizes PID + Odometry
*/

class SkidSteerDrive : public Drivetrain {
    public:
        /**
         * Initializes the SkidSteerDrive class with pointers to motors
         * @param tLeft Pointer to top left motor
         * @param tRight Pointer to top right motor
         * @param bLeft Pointer to bottom left motor
         * @param bRight Pointer to bottom right motor
        */
        SkidSteerDrive(pros::Motor *tLeft, pros::Motor *tRight, pros::Motor *bLeft, pros::Motor *bRight);

        /**
         * Drives chassis forward at specific speed
         * @param speed The speed in range [-127, 127]
        */ 
        void forward(double speed) override;

        /**
         * Rotate chassis clockwise at specific speed
         * @param speed The speed in range [-127, 127]
        */ 
        void rotate(double speed) override;

        /**
         * Stop providing power to motors
        */
        void stop() override;

        /**
        * Drive robot in tank drive controller layout
        * @param leftSpeed Speed provided to left side of chassis, in range [-127, 127]
        * @param rightSpeed Speed provided to right side of chassis, in range [-127, 127]
        * @param threshold Threshold of value before rounding to 0
        */
        void tank(double leftSpeed, double rightSpeed, double threshold = 0) override;

        /**
        * Drive robot in arcade drive controller layout
        * @param forward Speed provided to move the chassis forward, in range [-127, 127]
        * @param yaw Speed provided to turn the chassis, in range [-127, 127]
        * @param threshold Threshold of value before rounding to 0
        */
        void arcade(double forwardSpeed, double yaw, double threshold = 0) override;
    
    private:
        pros::Motor *tLeft; // Top left motor
        pros::Motor *tRight; // Top right motor      
        pros::Motor *bLeft; // Bottom left motor
        pros::Motor *bRight; // Bottom right motor
};