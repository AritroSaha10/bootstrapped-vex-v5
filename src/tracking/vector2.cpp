#include "tracking.h"
#include "main.h"

Vector2::Vector2(double x, double y) {
    this->x = x;
    this->y = y;
}

Vector2::Vector2() {
    this->x = 0;
    this->y = 0;
}

double Vector2::getMagnitude() {
    // Use pythagorean theorem
    return sqrt(pow(this->x, 2) + pow(this->y, 2));
}

double Vector2::getAngle() {
    return atan2(this->y, this->x);
}

Vector2 Vector2::normalize() {
    // Divide x and y by magnitude to retain direction
    return Vector2(this->x / this->getMagnitude(), this->y / this->getMagnitude());
}

Vector2 operator+(const Vector2 &v1, const Vector2 &v2) {
    return Vector2(v1.x + v2.x, v1.y + v2.y);
}

Vector2 operator-(const Vector2 &v1, const Vector2 &v2) {
    return Vector2(v1.x - v2.x, v1.y - v2.y);
}

Vector2 operator*(const Vector2 &v1, const double scalar) {
    return Vector2(v1.x * scalar, v1.y * scalar);
}