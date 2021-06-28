#include "main.h"

/**
 * Class object to control a nonholomic / "tank drive" robot drivetrain
 * Utilizes PID + Odometry
*/
class TankDrive {
    public:
        /**
         * Initializes the TankDrive class with pointers to motors
         * @param tLeft Pointer to top left motor
         * @param tRight Pointer to top right motor
         * @param bLeft Pointer to bottom left motor
         * @param bRight Pointer to bottom right motor
        */
        TankDrive(pros::Motor *tLeft, pros::Motor *tRight, pros::Motor *bLeft, pros::Motor *bRight);

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

    private:      
        pros::Motor *tLeft; // Top left motor      
        pros::Motor *tRight; // Top right motor      
        pros::Motor *bLeft; // Bottom left motor
        pros::Motor *bRight; // Bottom right motor
};