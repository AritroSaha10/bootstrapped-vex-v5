/**
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
double degToRad(double r);

/**
 * Class object to represent a vector within a 2 dimensional space
*/
class Vector2 {
    public:
        /**
         * Initializes the Vector2 class with preloaded x and y values
         * @param x x value of the vector
         * @param y y value of the vector
        */
        Vector2(double x, double y);

        Vector2(); // Initializes the Vector2 class

        double getX(); // Returns the x value of the vector
        double getY(); // Returns the y value of the vector

        double getMagnitude(); // Returns the magnitude of the vector
        double getAngle(); // Returns the angle of the vector

        Vector2 normalize(); // Normalizes vector

        // Arithmetic functions

        friend Vector2 operator+(const Vector2 &v1, const Vector2 &v2); // Vector addition
        friend Vector2 operator-(const Vector2 &v1, const Vector2 &v2); // Vector subtraction
        friend Vector2 operator*(const Vector2 &v1, double scalar); // Scalar multiplication of vector
    private:
        double x, y;
};

/**
 * Class object to represent the position info of the robot
*/
class TrackingData {
    public:
        /**
         * Initializes the TrackingData class with preloaded location and heading values
         * @param x x value of the location
         * @param y y value of the location
         * @param h heading value of the location
        */
        TrackingData(double x, double y, double h);

        //! Are these necessary if we can just return the vec?

        double getX(); // Return x value of position
        double getY(); // Return y value of position
        double getHeading(); // Return heading

        Vector2 getPos(); // Return position in Vector2 form
        Vector2 getForward(); // Return the forward in Vec2 form

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
        Vector2 pos;
        double heading;
};

/**
 * Rotate the vector by a certain angle
 * @param vec Vector to rotate
 * @param r Angle to rotate by
*/
double rotateVector(Vector2 &vec, double angle);

/**
 * Convert vector to local coordinates
 * @param r Vector to convert
*/
double toLocalCoordinates(Vector2 &vec);

/**
 * Convert vector to global coordinates
 * @param r Vector to convert
*/
double toGlobalCoordinates(Vector2 &vec);

/**
 * Main robot tracking function, runs as a PROs task
 * @param param Placeholder parameter required for PROs tasks
*/
void tracking(void* param);

#endif