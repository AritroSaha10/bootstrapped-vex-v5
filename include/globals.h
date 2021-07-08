/**
 * \file globals.h
 * 
 * \brief Contains all the global variables used throughout the project.
 * 
 * Contains global variables such as motors and encoders 
 * that are used throughout the project.
*/

#pragma once

#include "main.h"
#include "driveSystems/SkidSteerDrive.h"
#include "driveSystems/drivetrainPID.h"
#include "displayController.h"
#include "tracking.h"

// Motors

// Drivetrain motors
extern pros::Motor tLeft; // Top left motor      
extern pros::Motor tRight; // Top right motor      
extern pros::Motor bLeft; // Bottom left motor
extern pros::Motor bRight; // Bottom right motor


// Encoders

// Drivetrain encoders
extern pros::ADIEncoder bEnc; // Back encoder
extern pros::ADIEncoder lEnc; // Left encoder
extern pros::ADIEncoder rEnc; // Right encoder


// Drivetrain
extern SkidSteerDrive* driveTrain;
extern DrivetrainPID driveTrainPID;

// Odometry tracking
extern TrackingData trackingData;

// Display controller
extern DisplayController display;

// Actual controller
extern pros::Controller masterController;