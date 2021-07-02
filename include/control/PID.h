/**
 * \file PID.h
 * 
 * \brief Contains classes (PIDInfo, PIDController) required for a PID control loop
*/

#ifndef _PID_H_
#define _PID_H_

/**
 * \brief Class object to store PID constants
*/
class PIDInfo {
    public:
        /**
         * The proportional gain
        */
        double p;

        /**
         * The integral gain
        */
        double i;

        /**
         * The derivative gain
        */
        double d;

        /**
         * Initializes the PIDInfo class with preloaded constants
         * @param p Proportional gain
         * @param i Integral gain
         * @param d Derivative gain
        */
        PIDInfo(double p, double i, double d);

        /**
         * Initializes the PIDInfo class
        */
        PIDInfo() {};
};

/**
 * \brief Class object to control a motor using PID
*/
class PIDController {
    private:
        double sense; // Current sensor value
        double speed; // Calculated new speed
        
        double lastError; // Last error value
        double error; // Calculated error from sensor value and target
        
        double integral; // Integral (sum of errors) during PID loop
        double derivative; // Derivative during PID loop

        double settleStart; // Time at which settling has started
        bool settling, settled = false; // Settle flags

        double tolerance; // Tolerance value until settlable
        double integralTolerance; // Integral tolerance for integral threshold (?)

        PIDInfo constants; // PID gain constants

    public:
        /**
         * The current target value for the controller
        */
        double target;
        
        /**
         * Initializes the PID Controller with preloaded values
         * @param target Current target
         * @param constants PID gain constants in PIDInfo form
         * @param tolerance Tolerance value for error until controller settles
         * @param integralTolerance Integral tolerance value for integral threshold
        */
        PIDController(double target, PIDInfo constants, double tolerance, double integralTolerance);

        /**
         * Run a step of PID calculations given new sensor data
         * @param newSense New sensor data
         * @return New speed after running calculations 
        */
        double step(double newSense);

        /**
         * Reset all PID controller values back to their defaults
        */
        void reset(); 

        /**
         * Get the error value
         * @return The current error, aka target - sensor value
        */
        double getError();

        /**
         * Check whether controller is settled or not
         * @return Controller's settled state as boolean
        */
        bool isSettled(); 
};

#endif