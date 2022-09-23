#include <iostream>
#include "gl.h"
#include <math.h>

using namespace std;

int main()
{
    glInit();
	glCreateWindow(1000, 1000);
	glViewPort(0, 0, 1000, 1000);
	// glBackground("star");
    // glMap("Raptor");
	glTexture("Raptor.bmp");
    glShader();
	float scaleFactor[3] = {0.02, 0.02, 0.02};
    // float scaleFactor[3] = {0.5, 0.5, 0.5};
	float translateFactor[3] = {0.08, -0.08, 0};
	// float translateFactor[3] = {-0.2, -0.2, 0};
	float rotationFactor[3] = {0, 0, 0};
	glLoadMatrix(scaleFactor, translateFactor, rotationFactor);
	float eye[3] = {0.7, 0, 1};
	float center[3] = {0, 0, 0};
	float up[3] = {0, 1, 0};
	glEye(eye, center, up);
	glObject("Raptor.obj");
	glDraw();
	glFinish();
	return 0;
}