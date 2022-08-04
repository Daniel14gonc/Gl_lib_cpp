#include "vector3.h"

Vector3::Vector3(float x, float y, float z)
{
    vec= new float[3];
    vec[0] = x;
    vec[1] = y;
    vec[2] = z;
}

float* Vector3::getCoordinates()
{
    return vec;
}

Vector3 Vector3::operator+(Vector3 other)
{
    float* temp = other.getCoordinates();
    Vector3 res(
        vec[0] + temp[0],
        vec[1] + temp[1],
        vec[2] + temp[2]
    );
    delete temp;
    return res;
}

Vector3 Vector3::operator-(Vector3 other)
{
    float* temp = other.getCoordinates();
    Vector3 res(
        vec[0] - temp[0],
        vec[1] - temp[1],
        vec[2] - temp[2]
    );
    delete temp;
    return res;
}

Vector3 Vector3::operator*(float k)
{
    Vector3 res(
        vec[0] * k,
        vec[1] * k,
        vec[2] * k
    );
    return res;
}

Vector3 Vector3::operator*(Vector3 other)
{
    float* temp = other.getCoordinates();
    Vector3 res(
        vec[1] * temp[2] - vec[2] * temp[1],
        vec[2] * temp[0] - vec[0] * temp[2],
        vec[0] * temp[1] - vec[1] * temp[0]
    );
    delete temp;
    return res;
}

float Vector3::dot(Vector3 other)
{
    float* temp = other.getCoordinates();
    float res = vec[0] * temp[0] + vec[1] * temp[1] + vec[2] * temp[2];
    delete temp;
    return res;
}

float Vector3::length()
{
    float temp = pow(vec[0], 2) + pow(vec[1], 2) + pow(vec[2], 2);
    return pow(temp, 0.5);
}

Vector3 Vector3::normalized()
{
    return *this * (1 / this->length());
}

string Vector3::to_string()
{
    return "V3(" + std::to_string(vec[0]) + ", " + 
    std::to_string(vec[1]) + ", " + std::to_string(vec[2]) + ")";
}