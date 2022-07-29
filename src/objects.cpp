#include <iostream>
#include "gl.h"

using namespace std;


int main()
{
	glInit();
	glCreateWindow(400, 400);
	glObject("cube2.obj");
	glFinish();
	return 0;
}