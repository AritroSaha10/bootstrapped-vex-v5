#include "main.h"

/**
 * Base class for different types of drivetrains, ex. holonomic, nonholonomic
 * This should not be used in normal code, please use the derrived classes
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
        virtual void forward(double speed);

        /**
         * Rotate chassis clockwise at specific speed
         * @param speed The speed in range [-127, 127]
        */ 
        virtual void rotate(double speed);

        /**
         * Stop providing power to motors
        */
        virtual void stop();

        /**
        * Drive robot in tank drive controller layout
        */
        virtual void tank(double leftSpeed, double rightSpeed, double threshold = 0);

        /**
        * Drive robot in arcade drive controller layout
        */
        virtual void arcade(double forwardSpeed, double yaw, double threshold = 0);
};