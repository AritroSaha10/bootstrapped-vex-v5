#include "globals.h"
#include "chassis.h"

SkidSteerDrive* driveTrain = new SkidSteerDrive(&tLeft, &tRight, &bLeft, &bRight);
DrivetrainPID driveTrainPID(driveTrain, driveConstants, turnConstants, 1, 1);