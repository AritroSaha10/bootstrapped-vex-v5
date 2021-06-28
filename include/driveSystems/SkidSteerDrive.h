#include "main.h"
#include "drivetrainPID.h"

/**
 * Class object to control a nonholomic / "tank drive" robot drivetrain
 * Utilizes PID + Odometry
*/

class SkidSteerDrive : public DrivetrainPID {
    public:
        /**
         * Initializes the SkidSteerDrive class with pointers to motors
         * @param tLeft Pointer to top left motor
         * @param tRight Pointer to top right motor
         * @param bLeft Pointer to bottom left motor
         * @param bRight Pointer to bottom right motor
        */
        SkidSteerDrive(pros::Motor *tLeft, pros::Motor *tRight, pros::Motor *bLeft, pros::Motor *bRight);

        /**
         * Moves the robot a certain amount of feet relative to its current position
         * @param feet The amount of ft to move forwards or back (positive value for forward, negative for back)
        */ 
        void move(double feet) override;

        /**
         * Moves the robot to a certain position on the field
         * @param x The x coordinate in ft
         * @param y The y coordinate in ft
        */ 
        void moveTo(double x, double y) override;

        /**
         * Rotates the robot a certain amount of degrees relative to its current rotation
         * @param degrees The amount of degrees to turn (positive for clockwise, negative for counter-clockwise)
        */ 
        void rotate(double degrees) override;

        /**
         * Rotates the robot to a specific degree
         * @param degrees The rotation degree
        */ 
       void rotateTo(double degrees) override;

    private:      
        pros::Motor *tLeft; // Top left motor      
        pros::Motor *tRight; // Top right motor      
        pros::Motor *bLeft; // Bottom left motor
        pros::Motor *bRight; // Bottom right motor
};