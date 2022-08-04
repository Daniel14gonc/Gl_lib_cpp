#include <iostream>
#include "gl.h"
#include "vector3.h"

using namespace std;


int main()
{
	Vector3 v(3, 4, 5);
    Vector3 u(2, 3, 5);
    Vector3 res = v * u;
    cout << v.normalized().to_string() << endl;
	return 0;
}