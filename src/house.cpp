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

	for (int i = 0; i < 100; i++)
	{
		glLine(-0.75, y0, -0.2, y1);
		y0 += 0.004;
		y1 += 0.004;
	}
	y0 = -0.45;
	y1 = -0.1;
	glColor(1, 0, 0);
	for (int i = 0; i < 100; i++)
	{	
		glLine(-0.2, y0, 0.6, y1);
		y0 += 0.004;
		y1 += 0.004;
	}
	glFinish();
	return 0;
}