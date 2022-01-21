#include "tracking.h"
#include "main.h"
#include "globals.h"
#include "chassis.h"
#include "serialLogUtil.h"
#include <math.h>

// Encoder deltas
float lDelta = 0; // Delta of distance travelled by left tracking wheel
float rDelta = 0; // Delta of distance travelled by right tracking wheel
float bDelta = 0; // Delta of distance travelled by back tracking wheel

// Real world distances
float lDist = 0; // lDelta in inches
float rDist = 0; // rDelta in inches
float bDist = 0; // bDelta in inches
float aDelta = 0; // Delta of angle in radians

// Previous encoder values
float lLast = 0; // Last value of left tracking wheel
float rLast = 0; // Last value of right tracking wheel
float bLast = 0; // Last value of back tracking wheel

// Total distances
float left = 0; // Total distance travelled by left tracking wheel
float right = 0; // Total distance travelled by right tracking wheel
float lateral = 0; // Total distance travelled laterally (measured from back tracking wheel)
float angle = 0; // Current arc angle

Vector2 globalPos(0, 0);

// Constants and macros
const float lrOffset = WHEELBASE / 2.0f; // Offset of the left / right tracking wheel from the center in terms of x axis
const float bOffset = -BACK_WHEEL_OFFSET; // Offset of the back tracking wheel from the center in terms of y axis (negative because its in the back)

// Conversion calculations
#define DRIVE_DEGREE_TO_INCH (M_PI * DRIVE_WHEEL_DIAMETER / 360) 
#define TRACKING_WHEEL_DEGREE_TO_INCH (M_PI * TRACKING_WHEEL_DIAMETER / 360)

bool printTracking = true;

// Actual tracking function that runs in BG
void tracking(void* parameter) {
    // Assuming that there are 3 encoders

    uint32_t printTime = pros::millis();
    
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
        left += lDist;
        right += rDist;
        lateral += bDist;

        // Calculate new absolute orientation
        float prevAngle = angle; // Previous angle, used for delta
        angle = (right - left) / WHEELBASE;

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
                2 * sin(aDelta / 2) * (bDist / aDelta - bOffset),
                2 * sin(aDelta / 2) * (rDist / aDelta - lrOffset)
            );
        }

        // Calculate the average orientation
        // If any issues arise, try changing aDelta to aDelta/2
        float avgAngle = -(prevAngle + (aDelta / 2));

        // Calculate global offset https://www.mathsisfun.com/polar-cartesian-coordinates.html
        float globalOffsetX = cos(avgAngle); // cos(θ) = x 
        float globalOffsetY = sin(avgAngle); // sin(θ) = y 

        // Finally, update the global position
        globalPos = Vector2(
            trackingData.getPos().getX() + (localPos.getY() * globalOffsetY) + (localPos.getX() * globalOffsetX),
            trackingData.getPos().getY() + (localPos.getY() * globalOffsetX) - (localPos.getX() * globalOffsetY)
        );

        // Update tracking data
        trackingData.update(globalPos, degToRad(myImu.get_rotation() + 90));
        
        // Debug print
        if (pros::millis() - printTime > 75 && printTracking) {
            // Only print every 75ms to reduce lag
            colorPrintf("X: %f, Y: %f, A: %f\n", 
                GREEN,
                trackingData.getPos().getX(), 
                trackingData.getPos().getY(), 
                radToDeg(trackingData.getHeading())
            );

            printTime = pros::millis();
        }
        
        pros::delay(10); // Max of 10ms
    }
}