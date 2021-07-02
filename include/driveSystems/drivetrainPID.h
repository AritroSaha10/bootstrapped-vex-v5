/**
 * \file drivetrainPID.h
 * 
 * \brief Contains headers for the Drivetrain PID class which serves as a wrapper class on top of the Drivetrain class to use PID + Odometry.
*/

#pragma once

#include "main.h"
#include "drivetrain.h"
#include "control/PID.h"
#include "tracking.h"

/**
 * \brief Wrapper class on top of Drivetrain class to implement PID + Odom on any drivetrain
*/
class DrivetrainPID {
    public:
        /**
         * Initializes the Drivetrain class
         * @param drivetrain The type of drivetrain (ex. SkidSteerDrive) used
         * @param driveConstants The PID gain constants for the drive PID controller
         * @param turnConstants The PID gain constants for the turn PID controller
         * @param tolerance The tolerance for both PID controllers before it can be considered settled
         * @param integralTolerance The threshold at which the integral will be used or not
        */
        DrivetrainPID(Drivetrain* drivetrain, PIDInfo driveConstants, PIDInfo turnConstants, double tolerance, double integralTolerance);

        /**
         * Destructor for class
        */
        ~DrivetrainPID();
        
        /**
         * Set the velocity based on the current and wanted position and angle
         * @param dir The direction as a Vector2
         * @param turn The angle in radians
        */
        void move(Vector2 dir, double turn);

        /**
         * Turn to the angle needed to reach a position, drive to the position, and then turn to the desired angle
         * @param target The position to reach as a Vector2
         * @param angle The angle desired at the end of the action in radians
        */
        void moveToOrientation(Vector2 target, double angle);

        /**
         * Move to a specific point on the field
         * @param target The position to reach as a Vector2
        */ 
        void moveToPoint(Vector2 target);

        /**
         * Move and turn to a specific point and orientation relative to the bot's current
         * position and orientation
         * @param offset The desired position relative to the robot's current position as a Vector2
         * @param aOffset The desired angle relative to the robot's current orientation in radians
        */
        void moveRelative(Vector2 offset, double aOffset);

        /**
         * Rotate the robot to the desired orientation
         * @param angle The desired rotation in radians
        */ 
        void rotateTo(double angle);

        /**
         * Returns the drive controller
        */ 
        PIDController* getDriveController() { return driveController; };

        /**
         * Returns the turn controller
        */ 
        PIDController* getTurnController() { return turnController; };
    
    private:
        // PID Drive Controller
        PIDController* driveController;

        // PID Turn Controller
        PIDController* turnController;

        // Pointer to drivetrain, note that it must refer to a derrived class
        Drivetrain* drivetrain;
};