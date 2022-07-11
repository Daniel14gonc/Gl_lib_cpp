#include "MyGl.h"

void MyGl::glInit()
{
	height = 0; width = 0;
}

void MyGl::glCreateWindow(int h, int w)
{
	height = h;
	width = w;
	frameBuffer = new unsigned char** [height];
	for(int i = 0; i < height; i++)
	{
		frameBuffer[i] = new unsigned char* [width];
	};
	glCLear();
}

void MyGl::glCLear()
{
	for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
        	frameBuffer[i][j] = new unsigned char[3];
        	frameBuffer[i][j][2] = (unsigned char) 200;
        	frameBuffer[i][j][1] = (unsigned char) 0;
        	frameBuffer[i][j][0] = (unsigned char) 0;
        }
    }
}

void MyGl::glFinish()
{
	render.write(frameBuffer, width, height);
	deleteMemory();
}

void MyGl::deleteMemory()
{
	for(int i = 0; i < height; i++)
	{
		for(int j = 0; j < height; j++)
		{
			delete[] frameBuffer[i][j];
		}
		delete[] frameBuffer[i];
	};
	frameBuffer = NULL;
}

void MyGl::glVertex(float x, float y)
{
	frameBuffer[(int)x][(int)y][2] = (unsigned char) 100;
	frameBuffer[(int)x][(int)y][1] = (unsigned char) 200;
	frameBuffer[(int)x][(int)y][0] = (unsigned char) 50;
}