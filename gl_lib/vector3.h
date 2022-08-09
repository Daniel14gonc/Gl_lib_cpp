#include <string>
#include <iostream>
#include <cmath>

using namespace std;

class Vector3
{
	private:
        // Array to store values of vector.
		float* vec;

	public:
        float* getCoordinates();
		
        Vector3(float, float, float);
        
        Vector3(float, float);

        float getX();

        float getY();
        
        float getZ();

        // Sum of arrays
        Vector3 operator+(Vector3);

        // Substraction of arrays
        Vector3 operator-(Vector3);

        // Constant multiplication of array.
        Vector3 operator*(float);

        // Cross product arrays.
        Vector3 operator*(Vector3);

        // Dot product.
        float dot(Vector3);

        float length();
        
        // Vector normalization.
        Vector3 normalized();
        
        string to_string();

        void round();
};