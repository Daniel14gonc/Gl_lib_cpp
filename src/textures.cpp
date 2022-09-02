#include <iostream>
#include "gl.h"
#include <math.h>

using namespace std;

void loadCamera(string angle)
{
	glInit();
	glCreateWindow(1500, 1500);
	glViewPort(0, 0, 1500, 1500);
	glMap("droid");
	glClear();
	glTexture("droid.bmp");
	float scaleFactor[3] = {0.007, 0.007, 0.007};
	float translateFactor[3] = {0.3, 0, 0};
	float rotationFactor[3] = {0, 0, 0};
	glLoadMatrix(scaleFactor, translateFactor, rotationFactor);
	float eye[3] = {0, 0, 1};
	float center[3] = {0, 0, 0};
	float up[3] = {0, 1, 0};

	if (angle == "low")
	{
		eye[1] = -0.4;
	}
	else if (angle == "high")
	{
		eye[1] = 0.8;
	}
	else if (angle == "dutch")
	{
		up[0] = 0.6;
	}
	glEye(eye, center, up);
	glObject("droid.obj");
	glDraw();
	glFinish();
}


int main()
{
	// Ingresar medium, low, high o dutch para diferentes angulos
	loadCamera("medium");
	return 0;
}