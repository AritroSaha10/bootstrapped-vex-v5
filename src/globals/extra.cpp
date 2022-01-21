#include "globals.h"
#include "main.h"
#include "chassis.h"

// Display controller
DisplayController display = DisplayController();

// Actual controller
pros::Controller masterController (pros::E_CONTROLLER_MASTER);

// IMU
pros::IMU myImu(IMU_PORT);