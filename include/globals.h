#pragma once

#include "main.h"
#include "driveSystems/SkidSteerDrive.h"
#include "driveSystems/drivetrainPID.h"

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
extern SkidSteerDrive driveTrain;
extern DrivetrainPID driveTrainPID;