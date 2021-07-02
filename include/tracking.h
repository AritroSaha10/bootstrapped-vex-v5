/**
 * \file tracking.h
 * 
 * \brief Tracking code to track the robots location and rotation on the field.
 * 
 * Tracking code to track the robots location and rotation on the 
 * field. Utilizes algorithm documented in "Introduction to Position Tracking" 
 * by the E-Bots Pilons, found here: https://thepilons.ca/wp-content/uploads/2018/10/Tracking.pdf
*/

#ifndef _TRACKING_H_
#define _TRACKING_H_

/**
 * Converts radians to degrees
 * @param r Radian unit to convert
*/
double radToDeg(double r);

/**
 * Converts degrees to radians
 * @param r Degrees unit to convert
*/
double degToRad(double d);

/**
 * \brief Class object to represent a vector within a 2 dimensional space
*/
class Vector2 {
    public:
        /**
         * Initializes the Vector2 class with preloaded x and y values
         * @param x x value of the vector
         * @param y y value of the vector
        */
        Vector2(double x, double y);

        /**
         * Initializes the Vector2 class with default values (0, 0)
        */
        Vector2();


        /**
         * Returns the x value of the vector
        */
        double getX() { return this->x; };

        /**
         * Returns the y value of the vector
        */
        double getY() { return this->y; };


        /**
         * Returns the magnitude of the vector
        */
        double getMagnitude();

        /**
         * Returns the angle of the vector
        */
        double getAngle();


        /**
         * Normalize the vector (change the length of the vector to 1 while retaining the direction)
         * @return Normalized version of the vector
        */
        Vector2 normalize(); 

        // Arithmetic functions

        /**
         * Simple vector addition
        */
        friend Vector2 operator+(const Vector2 &v1, const Vector2 &v2);
        /**
         * Simple vector subtraction
        */
        friend Vector2 operator-(const Vector2 &v1, const Vector2 &v2);
        /**
         * Scalar and vector multiplication
        */
        friend Vector2 operator*(const Vector2 &v1, const double scalar);
    
    private:
        /**
         * The x value of the vector
        */
        double x;
        /**
         * The y value of the vector
        */
        double y;
};

/**
 * \brief Class object to represent the position info of the robot
*/
class TrackingData {
    public:
        /**
         * Initializes the TrackingData class with preloaded location and heading values
         * @param x x value of the location
         * @param y y value of the location
         * @param h heading value
        */
        TrackingData(double x, double y, double h);

        /**
         * Get the heading angle of the current tracking data
         * @return The heading angle of the robot
        */
        double getHeading(); 

        /**
         * Get the position
         * @return Robot position as Vector2
        */
        Vector2 getPos(); 
        /**
         * Get the forward of the robot
         * @return Robot forward as Vector2
        */
        Vector2 getForward(); 

        /**
         * Update the tracking data given position and heading values
         * @param newX The new X coordinate of the robot
         * @param newY The new Y coordinate of the robot
         * @param newH The new heading of the robot
        */ 
        void update(double newX, double newY, double newH);

        /**
         * Update the tracking data given position and heading values
         * @param newPos The new position of the robot in Vec2 form
         * @param newH The new heading of the robot
        */ 
        void update(Vector2 newPos, double newH);

    private:
        /**
         * Current position of the robot represented as a Vector2 (units: ft)
        */
        Vector2 pos;
        /**
         * Current heading (angle) of the robot
        */
        double heading;
};

/**
 * Rotate the vector by a certain angle
 * @param vec Vector to rotate
 * @param r Angle to rotate by
*/
Vector2 rotateVector(Vector2 vec, double angle);

/**
 * Convert vector to local coordinates
 * @param r Vector to convert
*/
Vector2 toLocalCoordinates(Vector2 vec);

/**
 * Convert vector to global coordinates
 * @param r Vector to convert
*/
Vector2 toGlobalCoordinates(Vector2 vec);

/**
 * Main robot tracking function, runs as a PROs task
 * @param param Placeholder parameter required for PROs tasks
*/
void tracking(void* param);

#endif