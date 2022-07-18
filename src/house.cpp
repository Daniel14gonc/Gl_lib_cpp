#include <iostream>
#include "gl.h"

using namespace std;


int main()
{
	glInit();
	glCreateWindow(500, 500);
	glViewPort(0, 0, 500, 500);
	float y0 = -0.15;
	float y1 = -0.45;

	glColor(0.7, 0, 0);
	// Pared lateral
	for (int i = 0; i < 100; i++)
	{
		glLine(-0.75, y0, -0.2, y1);
		y0 += 0.004;
		y1 += 0.004;
	}

	//Pared frontal
	y0 = -0.45;
	y1 = -0.1;
	for (int i = 0; i < 100; i++)
	{	
		glLine(-0.2, y0, 0.6, y1);
		y0 += 0.004;
		y1 += 0.004;
	}

	//Techo lateral
	glColor(1, 0, 0);
	y0 = 0.25;
	y1 = 0.8;
	float x0 = -0.75;
	float x1 = -0.35;
	for (int i = 0; i < 5450; i++)
	{
		glLine(x0, y0, x1, y1);
		x0 += 0.0001;
		y0 -= 0.000055;
		x1 += 0.0001;
		y1 -= 0.000055;
	}	

	//Puerta
	glColor(1, 1, 1);
	y0 = -0.3;
	y1 = -0.215;
	for (int i = 0; i < 50; i++)
	{	
		glLine(0.15, y0, 0.35, y1);
		y0 += 0.004;
		y1 += 0.004;
	}

	glFinish();
	return 0;
}