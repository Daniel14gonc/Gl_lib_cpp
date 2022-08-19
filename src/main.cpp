#include <iostream>
#include "gl.h"
#include "matrix.hpp"
#include "matrix.hpp"


using namespace std;

template<typename T>
void print(T a)
{
	cout << a << endl;
}

template<int N>
class Array
{
	private:
		float array[N];
	
	public:
		int length()
		{
			return N;
		}
};



int main()
{
	/*glInit();
	glCreateWindow(100, 100);
	glViewPort(50, 50, 20, 20);
	glVertex(0, 0);
	glFinish();
	return 0;*/
	Matrix<2, 2> a = {{{2, 3}, {3, 2}}};
	Matrix<2, 2> b = {{{2, 3}, {3, 2}}};
	Matrix<2, 2> c = a * b;
	print(c.to_string());
	return 0;
}