#include <iostream>
#include "gl.h"
#include <math.h>

using namespace std;

int main()
{
    glInit();
	glCreateWindow(1500, 1500);
	glViewPort(0, 0, 1500, 1500);
    glClearColor(0, 0, 0);
	glMap("earth");
    glShader();
	glClear();
	glTexture("earth.bmp");
	float scaleFactor[3] = {0.002, 0.002, 0.002};
    // float scaleFactor[3] = {0.5, 0.5, 0.5};
	float translateFactor[3] = {0.9, 0.1, 0};
	// float translateFactor[3] = {-0.2, -0.2, 0};
	float rotationFactor[3] = {0, 0, 0};
	glLoadMatrix(scaleFactor, translateFactor, rotationFactor);
	float eye[3] = {0.3, 0, 1};
	float center[3] = {0, 0, 0};
	float up[3] = {0, 1, 0};
	glEye(eye, center, up);
	glObject("earth.obj");
	glDraw();
	glFinish();
	return 0;
}