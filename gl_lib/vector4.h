#include <string>
#include <iostream>
#include <cmath>
#pragma once

using namespace std;

class Vector4
{
	private:
        // Array to store values of vector.
		float* vec;

	public:
        float* getCoordinates();
		
        Vector4(float, float, float z = 0, float w = 0);

        float getX();

        float getY();
        
        float getZ();

        // Sum of arrays
        Vector4 operator+(Vector4);

        // Substraction of arrays
        Vector4 operator-(Vector4);

        // Constant multiplication of array.
        Vector4 operator*(float);
        
        // Dot product.
        float dot(Vector4);

        float length();
        
        // Vector normalization.
        Vector4 normalized();
        
        string to_string();

        void round();

        float getElement(int);

        void setElement(int, float);
};