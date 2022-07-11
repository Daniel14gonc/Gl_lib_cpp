#include <iostream>
#include "gl.h"

using namespace std;

int algo = 3;

int main()
{
	glCreateWindow(100, 100);
	glVertex(0, 0);
	glFinish();
	return 0;
}