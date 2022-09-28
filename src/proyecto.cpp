#include <iostream>
#include "gl.h"
#include <math.h>

using namespace std;

int main()
{
    glInit();
	glCreateWindow(900, 900);
	glClear();
	glBackground("land7");


	float eye[3] = {0.7, 0, 1};
	float center[3] = {0, 0, 0};
	float up[3] = {0, 1, 0};

	glViewPort(0, 0, 500, 500);
	glShader();
	float scaleFactor[3] = {0.002, 0.002, 0.002};
    // float scaleFactor[3] = {0.5, 0.5, 0.5};
	float translateFactor[3] = {0.01, 2, 0};
	// float translateFactor[3] = {-0.2, -0.2, 0};
	float rotationFactor[3] = {0, 0, 0};
	glLoadMatrix(scaleFactor, translateFactor, rotationFactor);
	glEye(eye, center, up);
	glObject("earth.obj");
	glDraw();
	glFinish();

	float scaleFactor1[3] = {0.01, 0.013, 0.01};
	float translateFactor1[3] = {0.5, -0.9, 0};
	float rotationFactor1[3] = {0, 0, 0};

	glViewPort(0, 0, 600, 600);
	glClearNormal();
	glTexture("Vol.bmp");
	glShader();
	float scaleFactor2[3] = {0.00035, 0.00045, 0.0002};
	glLoadMatrix(scaleFactor2, translateFactor1, rotationFactor1);
	glEye(eye, center, up);
	glObject("Vol.obj");
	glDraw();

	

	glViewPort(500, 0, 300, 500);
	// Uso de normal map
	Texture* tN = new Texture("RaptorN.bmp");
	glNormal(tN);
	glTexture("Raptor.bmp");
    glShader();
	float scaleFactor3[3] = {0.01, 0.01, 0.01};
	float translateFactor2[3] = {0.08, -0.7, 1};
	glLoadMatrix(scaleFactor1, translateFactor2, rotationFactor1);
	
	glEye(eye, center, up);
	glObject("Raptor.obj");
	glDraw();

	tN = new Texture("RockN.bmp");
	glNormal(tN);
	glTexture("Rock.bmp");
	float scaleFactor4[3] = {0.006, 0.006, 0.006};
	float translateFactor4[3] = {-0.3, -0.7, 0};
	float rotationFactor4[3] = {0.9, 0, 0};
	glLoadMatrix(scaleFactor4, translateFactor4, rotationFactor4);
	/*float eye[3] = {-0.7, 0, 1};
	float center[3] = {0, 0, 0};
	float up[3] = {0, 1, 0};*/
	glEye(eye, center, up);
	glObject("Rock.obj");
	glDraw();
	
	glFinish();
	return 0;
}