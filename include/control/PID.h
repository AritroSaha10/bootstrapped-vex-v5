/**
 * Controller code for control loop using PID to accurately 
 * reach a target
*/

#ifndef _PID_H_
#define _PID_H_

/**
 * Class object to store PID constants
*/
class PIDInfo {
    public:
        double p; // Proportional constant
        double i; // Integral constant
        double d; // Derivative constant

        /**
         * Initializes the PIDInfo class with preloaded constants
         * @param p Proportional constant
         * @param i Integral constant
         * @param d Derivative constant
        */
        PIDInfo(double p, double i, double d);

        /**
         * Initializes the PIDInfo class
        */
        PIDInfo() {};
};

/**
 * Class object to control a motor using PID
*/
class PIDController {
    private:
        double sense; // Current sensor value
        double target; // Target value
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
         * Initializes the PID Controller with preloaded values
         * @param target Current target
         * @param constants PID gain constants in PIDInfo form
         * @param tolerance Tolerance value for error until controller settles
         * @param bRight Integral tolerance value for integral threshold
        */
        PIDController(double target, PIDInfo constants, double tolerance, double integralTolerance);

        /**
         * Run a step of PID calculations given new sensor data
         * @param newSense New sensor data
        */
        double step(double newSense);
        void reset(); // Reset PID controller values

        double getError(); // Get the current error of the controller
        bool isSettled(); // Check if the controller is settled
};

#endif