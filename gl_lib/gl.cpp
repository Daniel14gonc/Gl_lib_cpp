#include "gl.h"
#include <iostream>

Render* render;
unsigned char*** frameBuffer;
int height, width;

namespace 
{
	void deleteMemory()
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

	int* calculatePosition(float x, float y)
	{
		int* coordinates = new int[2];
		int xC, yC;
		xC = (x + 1) * 0.5 * width;
		yC = (y + 1) * 0.5 * height;
		
		coordinates[0] = xC;
		coordinates[1] = yC;

		return coordinates;
	}
}

void glInit()
{
	height = 0; width = 0;
	render = new Render();
}

void glCreateWindow(int h, int w)
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

void glCLear()
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

void glFinish()
{
	(*render).write(frameBuffer, width, height);
	deleteMemory();
}



void glVertex(float x, float y)
{
	int *coordinates = calculatePosition(x, y);
	int xC = coordinates[0];
	int yC = coordinates[1];
	frameBuffer[xC][yC][2] = (unsigned char) 100;
	frameBuffer[xC][yC][1] = (unsigned char) 200;
	frameBuffer[xC][yC][0] = (unsigned char) 50;
	delete[] coordinates;
}