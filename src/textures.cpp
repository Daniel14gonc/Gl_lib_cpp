#include <iostream>
#include "gl.h"

using namespace std;


int main()
{
	glInit();
	glMap("earth.bmp");
	glCreateWindow(1500, 1500);
	glTexture("earth.bmp");
	glObject("earth.obj");
	glFinish();
	return 0;
}