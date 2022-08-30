#include <iostream>
#include "gl.h"
#include <math.h>

using namespace std;


int main()
{
	glInit();
	glCreateWindow(1500, 1500);
	glMap("droid");
	glClear();
	glTexture("droid.bmp");
	float scaleFactor[3] = {5, 5, 5};
	int translateFactor[3] = {1000, 700, 0};
	float rotationFactor[3] = {0, 0, 0};
	glLoadMatrix(scaleFactor, translateFactor, rotationFactor);
	float eye[3] = {500, 100, 100};
	float center[3] = {0, 0, 0};
	float up[3] = {0, 1, 0};
	glEye(eye, center, up);
	glObject("droid.obj");
	glDraw();
	glFinish();
	return 0;
}