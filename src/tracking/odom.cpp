#include "tracking.h"
#include "main.h"
#include "globals.h"
#include "chassis.h"
#include <math.h>

// Encoder deltas
float lDelta; // Delta of distance travelled by left tracking wheel
float rDelta; // Delta of distance travelled by right tracking wheel
float bDelta; // Delta of distance travelled by back tracking wheel

// Real world distances
float lDist; // lDelta in inches
float rDist; // rDelta in inches
float bDist; // bDelta in inches
float aDelta; // Delta of angle in radians

// Previous encoder values
float lLast; // Last value of left tracking wheel
float rLast; // Last value of right tracking wheel
float bLast; // Last value of back tracking wheel

// Constants and macros
const float lrOffset = WHEELBASE / 2.0f; // Offset of the left / right tracking wheel from the center in terms of x axis
const float bOffset = -BACK_WHEEL_OFFSET; // Offset of the back tracking wheel from the center in terms of y axis (negative because its in the back)

// Conversion calculations
#define DRIVE_DEGREE_TO_INCH (M_PI * DRIVE_WHEEL_DIAMETER / 360) 
#define TRACKING_WHEEL_DEGREE_TO_INCH (M_PI * TRACKING_WHEEL_DIAMETER / 360)

// Actual tracking function that runs in BG
void tracking(void* parameter) {
    // Assuming that there are 3 encoders
    // Also, I don't know if this works

    // Initialize variables
    lLast = 0; // Last encoder value of left
    rLast = 0; // Last encoder value of right
    bLast = 0; // Last encoder value of back

    Vector2 globalPos(0, 0);

    float left = 0; // Total distance travelled by left tracking wheel
    float right = 0; // Total distance travelled by right tracking wheel
    float lateral = 0; // Total distance travelled laterally (measured from back tracking wheel)
    float angle = 0; // Current arc angle

    // Reset encoders to 0 before starting
    lEnc.reset();
    rEnc.reset();
    bEnc.reset();

    // Tracking loop
    while (true) {
        Vector2 localPos;

        // Get encoder data
        float lEncVal = lEnc.get_value();
        float rEncVal = rEnc.get_value();
        float bEncVal = bEnc.get_value();

        // Calculate delta values
        lDelta = lEncVal - lLast;
        rDelta = rEncVal - rLast;
        bDelta = bEncVal - bLast;

        // Calculate IRL distances from deltas
        lDist = lDelta * TRACKING_WHEEL_DEGREE_TO_INCH;
        rDist = rDelta * TRACKING_WHEEL_DEGREE_TO_INCH;
        bDist = bDelta * TRACKING_WHEEL_DEGREE_TO_INCH;

        // Update last values for next iter since we don't need to use last values for this iteration
        lLast = lEncVal;
        rLast = rEncVal;
        bLast = bEncVal;

        // Update total distance vars
        left += lEncVal;
        right += rEncVal;
        lateral += bEncVal;

        // Calculate new absolute orientation
        float prevAngle = angle; // Previous angle, used for delta
        angle = (left - right) / (lrOffset * 2.0f);

        // Get angle delta
        aDelta = angle - prevAngle;

        // Calculate using different formulas based on if orientation change
        float avgLRDelta = (lDist + rDist) / 2; // Average of delta distance travelled by left and right wheels
        if (aDelta == 0.0f) {
            // Set the local positions to the distances travelled since the angle didn't change
            localPos = Vector2(bDist, avgLRDelta);
        } else {
            // Use the angle to calculate the local position since angle did change
            localPos = Vector2(
                2 * sin(angle / 2) * (bDist / aDelta + bOffset),
                2 * sin(angle / 2) * (avgLRDelta / aDelta + lrOffset)
            );
        }

        // Calculate the average orientation
        float avgAngle = prevAngle + aDelta / 2;

        // Calculate global offset https://www.mathsisfun.com/polar-cartesian-coordinates.html
        float globalOffsetX = cos(avgAngle); // cos(θ) = x (i think)
        float globalOffsetY = sin(avgAngle); // sin(θ) = y (i think)

        // Finally, update the global position
        globalPos = Vector2(
            globalPos.getX() + (localPos.getY() * globalOffsetY) + (localPos.getX() * globalOffsetX),
            globalPos.getY() + (localPos.getY() * globalOffsetX) - (localPos.getX() * globalOffsetY)
        );

        // Update tracking data
        trackingData.update(globalPos.getX(), globalPos.getY(), angle);

        // Debug print (can't use display so just throw to serial)
        printf("X: %f, Y: %f, A: %f", 
                trackingData.getPos().getX(), 
                trackingData.getPos().getY(), 
                radToDeg(trackingData.getHeading()));
        
        pros::delay(10); // Max of 10ms
    }
}