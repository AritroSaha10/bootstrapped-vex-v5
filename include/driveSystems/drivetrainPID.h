#pragma once

#include "main.h"
#include "drivetrain.h"
#include "control/PID.h"

/**
 * Wrapper class on top of Drivetrain class to implement PID + Odom on any drivetrain
*/
class DrivetrainPID {
    public:
        /**
         * Initializes the Drivetrain class
         * @param drivetrain The type of drivetrain (ex. SkidSteerDrive) used
        */
        DrivetrainPID(Drivetrain* drivetrain);

        /**
         * Moves the robot a certain amount of feet relative to its current position
         * @param feet The amount of ft to move forwards or back (positive value for forward, negative for back)
        */ 
        void move(double feet);

        /**
         * Moves the robot to a certain position on the field
         * @param x The x coordinate in ft
         * @param y The y coordinate in ft
        */ 
        void moveTo(double x, double y);

        /**
         * Rotates the robot a certain amount of degrees relative to its current rotation
         * @param degrees The amount of degrees to turn (positive for clockwise, negative for counter-clockwise)
        */ 
        void rotate(double degrees);

        /**
         * Rotates the robot to a specific degree
         * @param degrees The rotation degree
        */ 
        void rotateTo(double degrees);

        /**
         * Returns if drivetrain is settled
        */ 
        bool isSettled() { return controller->isSettled(); };
    
    private:
        // PID Controller
        PIDController* controller;

        // Pointer to drivetrain, note that it must refer to a derrived class
        Drivetrain* drivetrain;
};