#include <iostream>
#include "gl.h"
#include "matrix.hpp"
#include "matrix.hpp"


using namespace std;

int main()
{
	glInit();
	glCreateWindow(100, 100);
	glViewPort(50, 50, 20, 20);
	glVertex(0, 0);
	glFinish();
	return 0;
}