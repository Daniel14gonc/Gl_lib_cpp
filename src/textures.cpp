#include <iostream>
#include "gl.h"

using namespace std;


int main()
{
	glInit();
	glMap("dr.bmp");
	glCreateWindow(1500, 1500);
	glTexture("dr.bmp");
	glObject("droid.obj");
	glFinish();
	return 0;
}