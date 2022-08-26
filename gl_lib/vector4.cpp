#include "vector4.h"
#include <cmath>

Vector4::Vector4(float x, float y, float z, float w)
{
    vec =  new float[4];
    vec[0] = x;
    vec[1] = y;
    vec[2] = z;
}

float* Vector4::getCoordinates()
{
    return vec;
}

float Vector4::getX()
{
    return vec[0];
}

float Vector4::getY()
{
    return vec[1];
}

float Vector4::getZ()
{
    return vec[2];
}

Vector4 Vector4::operator+(Vector4 other)
{
    float* temp = other.getCoordinates();
    Vector4 res(
        vec[0] + temp[0],
        vec[1] + temp[1],
        vec[2] + temp[2],
        vec[3] + temp[3]
    );
    // delete temp;
    return res;
}

Vector4 Vector4::operator-(Vector4 other)
{
    float* temp = other.getCoordinates();
    Vector4 res(
        vec[0] - temp[0],
        vec[1] - temp[1],
        vec[2] - temp[2],
        vec[3] - temp[3]
    );
    // delete temp;
    return res;
}

Vector4 Vector4::operator*(float k)
{
    Vector4 res(
        vec[0] * k,
        vec[1] * k,
        vec[2] * k,
        vec[3] * k
    );
    return res;
}

float Vector4::dot(Vector4 other)
{
    float* temp = other.getCoordinates();
    float res = vec[0] * temp[0] + vec[1] * temp[1] + vec[2] * temp[2] + vec[3] * vec[3];
    // delete temp;
    return res;
}

float Vector4::length()
{
    float temp = pow(vec[0], 2) + pow(vec[1], 2) + pow(vec[2], 2) + pow(vec[3], 2);
    return pow(temp, 0.5);
}

Vector4 Vector4::normalized()
{
    return *this * (1 / this->length());
}

string Vector4::to_string()
{
    return "V4(" + std::to_string(vec[0]) + ", " + 
    std::to_string(vec[1]) + ", " + std::to_string(vec[2]) +
    std::to_string(vec[3]) + ")";
}

void Vector4::round()
{
    vec[0] = std::round(vec[0]);
    vec[1] = std::round(vec[1]);
    vec[2] = std::round(vec[2]);
    vec[3] = std::round(vec[3]);
}

float Vector4::getElement(int k)
{
    return vec[k];
}

void Vector4::setElement(int k, float value)
{
    vec[k] = value;
}