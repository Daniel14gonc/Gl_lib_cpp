#include <iostream>
#include "gl.h"
#include <math.h>

using namespace std;

int main()
{
    glInit();
	glCreateWindow(800, 500);
	glViewPort(0, 0, 500, 500);

	// glBackground("eruption");
	glBackground("star");
    // glMap("Raptor");

	/*Texture* tN = new Texture("ZealotN.bmp");
	glNormal(tN);
	glTexture("Rock.bmp");
    glShader();
	float scaleFactor[3] = {0.006, 0.006, 0.006};
    // float scaleFactor[3] = {0.5, 0.5, 0.5};
	float translateFactor[3] = {0.08, -0.08, 0};
	// float translateFactor[3] = {-0.2, -0.2, 0};
	float rotationFactor[3] = {0.9, 0, 0};
	glLoadMatrix(scaleFactor, translateFactor, rotationFactor);
	
	glEye(eye, center, up);
	glObject("Rock.obj");
	glDraw();

	tN = new Texture("RaptorN.bmp");
	glNormal(tN);
	glTexture("Raptor.bmp");
    glShader();*/
	float scaleFactor1[3] = {0.0001, 0.0001, 0.0001};
    // float scaleFactor[3] = {0.5, 0.5, 0.5};
	float translateFactor1[3] = {0.08, -0.08, 0};
	// float translateFactor[3] = {-0.2, -0.2, 0};
	float rotationFactor1[3] = {0, 0, 0};
	// glLoadMatrix(scaleFactor1, translateFactor1, rotationFactor1);
	/*float eye[3] = {-0.7, 0, 1};
	float center[3] = {0, 0, 0};
	float up[3] = {0, 1, 0};*/
	/*glEye(eye, center, up);
	glObject("Raptor.obj");
	glDraw();*/

	float eye[3] = {-0.7, 0, 1};
	float center[3] = {0, 0, 0};
	float up[3] = {0, 1, 0};
	glClearNormal();

	glTexture("Vol.bmp");
	glShader();
	float scaleFactor2[3] = {0.00009, 0.0001, 0.00009};
	glLoadMatrix(scaleFactor2, translateFactor1, rotationFactor1);
	glEye(eye, center, up);
	glObject("Vol.obj");
	glDraw();
	
	glFinish();
	return 0;
}