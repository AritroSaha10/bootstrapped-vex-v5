#include "main.h"
#include "drivetrain.h"

/**
 * Base class for different types of drivetrains, ex. holonomic, nonholonomic with PID and Odom
 * This should not be used in normal code, please use the derrived classes
*/
class DrivetrainPID {
    public:
        /**
         * Initializes the Drivetrain class
        */
        DrivetrainPID() {};

        /**
         * Moves the robot a certain amount of feet relative to its current position
         * @param feet The amount of ft to move forwards or back (positive value for forward, negative for back)
        */ 
        virtual void move(double feet);

        /**
         * Moves the robot to a certain position on the field
         * @param x The x coordinate in ft
         * @param y The y coordinate in ft
        */ 
        virtual void moveTo(double x, double y);

        /**
         * Rotates the robot a certain amount of degrees relative to its current rotation
         * @param degrees The amount of degrees to turn (positive for clockwise, negative for counter-clockwise)
        */ 
        virtual void rotate(double degrees);

        /**
         * Rotates the robot to a specific degree
         * @param degrees The rotation degree
        */ 
        virtual void rotateTo(double degrees);

        /**
         * Returns if drivetrain is settled
        */ 
        bool isSettled() { return settled; };
    
    private:
        bool settled;
};