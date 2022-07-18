#include "render.h"
#include <iostream>
#include <fstream>
#include <cmath>

using namespace std;

Render::Render()
{
	clearColor = new unsigned char[3];
	clearColor[2] = (unsigned char) (255);
	clearColor[1] = (unsigned char) (255);
	clearColor[0] = (unsigned char) (255); 

	color = new unsigned char[3];
	color[2] = (unsigned char) (0);
	color[1] = (unsigned char) (0);
	color[0] = (unsigned char) (0); 
}

void Render::startBuffer(int w, int h)
{
	height = h;
	width = w;
	frameBuffer = new unsigned char** [height];
	for(int i = 0; i < height; i++)
	{
		frameBuffer[i] = new unsigned char* [width];
	};
	x0 = 0;
	y0 = 0;
	widthV = w;
	heightV = h;
	clear();
}

void Render::clear()
{
	for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
        	frameBuffer[i][j] = new unsigned char[3];
        	frameBuffer[i][j][2] = clearColor[2];
        	frameBuffer[i][j][1] = clearColor[1];
        	frameBuffer[i][j][0] = clearColor[0];
        }
    }
}

// Clamping
void Render::changeClearColor(float r, float g, float b)
{
	if (r > 1) r = 1;
	if (r < 0) r = 0;
	if (g > 1) g = 1;
	if (g < 0) g = 0;
	if (b > 1) b = 1;
	if (b < 0) b = 0;
	clearColor[2] = (int)(r*255);
	clearColor[1] = (int)(g*255);
	clearColor[0] = (int)(b*255);
}

int Render::write()
{

	// Define a padding size if width in bytes is not multiple of 4.
	unsigned char padding[3] = {0, 0, 0};
	int paddingSize = (4 - (width * 3) % 4) % 4;
	int imgSize = width * height * 3;

	// Define the new width with padding size.
	int stride = (width*3) + paddingSize;
	int fileSize = 14 + 40 + (height * stride);

	// Get the byte array for the file header and size header.
	unsigned char* fileHeader = createFileHeader(fileSize);
	unsigned char* fileSizeH = createSizeHeader(width, height);

	FILE* imageFile;
	imageFile = fopen("image.bmp", "wb");

	// Write the headers into file.
	fwrite(fileHeader, 1, 14, imageFile);
	fwrite(fileSizeH, 1, 40, imageFile);

	// Write the image into the file.
    for (int i = 0; i < height; i++) {
    	for(int j = 0; j < width; j++)
    	{
    		fwrite((unsigned char*)frameBuffer[i][j], 3, 1, imageFile);
    	}

    	fwrite(padding, 1, paddingSize, imageFile);
    }


	fclose(imageFile);
	// deleteMemory();
	return 0;
}

unsigned char* Render::createFileHeader(int fileSize)
{
	static unsigned char bmpFileHeader [14] = {
		0, 0,
		0, 0, 0, 0, 
		0, 0,  
		0, 0,  
		0, 0, 0, 0
	};

	bmpFileHeader[0] = (unsigned char)('B');
	bmpFileHeader[1] = (unsigned char)('M');
	bmpFileHeader[2] = (unsigned char)(fileSize);
	bmpFileHeader[3] = (unsigned char)(fileSize >> 8);
	bmpFileHeader[4] = (unsigned char)(fileSize >> 16);
	bmpFileHeader[5] = (unsigned char)(fileSize >> 24);
	bmpFileHeader[10] = (unsigned char)(54);

	return bmpFileHeader;
}

unsigned char* Render::createSizeHeader(int width, int height)
{
	int imgSize = width * height *3;
	static unsigned char bmpFileSize [40] = {
		0, 0, 0, 0,
		0, 0, 0, 0,
		0, 0, 0, 0,
		0, 0,
		0, 0,
		0, 0, 0, 0,
		0, 0, 0, 0,
		0, 0, 0, 0,
		0, 0, 0, 0,
		0, 0, 0, 0,
		0, 0, 0, 0
	};

	bmpFileSize[0] = (unsigned char)(40);
	bmpFileSize[4] = (unsigned char)(width);
	bmpFileSize[5] = (unsigned char)(width >> 8);
	bmpFileSize[6] = (unsigned char)(width >> 16);
	bmpFileSize[7] = (unsigned char)(width >> 24);
	bmpFileSize[8] = (unsigned char)(height);
	bmpFileSize[9] = (unsigned char)(height >> 8);
	bmpFileSize[10] = (unsigned char)(height >> 16);
	bmpFileSize[11] = (unsigned char)(height >> 24);
	bmpFileSize[12] = (unsigned char)(1);
	bmpFileSize[14] = (unsigned char)(24);
	bmpFileSize[20] = (unsigned char)(imgSize);
	bmpFileSize[20] = (unsigned char)(imgSize >> 8);
	bmpFileSize[20] = (unsigned char)(imgSize >> 16);
	bmpFileSize[20] = (unsigned char)(imgSize >> 24);


	return bmpFileSize;
}

void Render::deleteMemory()
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

int* Render::calculatePosition(float x, float y)
{
	int* coordinates = new int[2];
	int xC, yC;
	xC = x0 + (x + 1) * 0.5 * (widthV - 1);
	yC = y0 + (y + 1) * 0.5 * (heightV - 1);
	coordinates[0] = xC;
	coordinates[1] = yC;

	return coordinates;
}

void Render::point(float x, float y)
{
	int *coordinates = calculatePosition(y, x);
	int xC = coordinates[0];
	int yC = coordinates[1];
	if (xC < width && yC < height && xC >= 0 && yC >= 0)
	{
		frameBuffer[xC][yC][2] = color[2];
		frameBuffer[xC][yC][1] = color[1];
		frameBuffer[xC][yC][0] = color[0];
	}
	delete[] coordinates;
}

void Render::pointLine(int x, int y)
{
	if (x < width && y < height && x  >= 0 && y >= 0)
	{
		frameBuffer[x][y][2] = color[2];
		frameBuffer[x][y][1] = color[1];
		frameBuffer[x][y][0] = color[0];
	}
}

// Clamping
void Render::changeColor(float r, float g, float b)
{
	if (r > 1) r = 1;
	if (r < 0) r = 0;
	if (g > 1) g = 1;
	if (g < 0) g = 0;
	if (b > 1) b = 1;
	if (b < 0) b = 0;
	color[2] = (int)(r*255);
	color[1] = (int)(g*255);
	color[0] = (int)(b*255);
}

void Render::viewPort(int x, int y, int w, int h)
{
	if(x < width && y < height && x >= 0 && y >= 0)
	{
		int* coordinates = calculatePosition(x, y);
		x0 = x;
		y0 = y;
		widthV = w;
		heightV = h;
		delete[] coordinates;
	}
}

void Render::drawLine(float a, float b, float c, float d)
{
	int *coordinates = calculatePosition(a, b);
	int x0 = coordinates[0];
	int y0 = coordinates[1];
	coordinates = calculatePosition(c, d);
	int x1 = coordinates[0];
	int y1 = coordinates[1];
	delete[] coordinates;

	float dy = abs(y1 - y0);
	float dx = abs(x1 - x0);
	float m = dy;

	bool steep = dy > dx;

	if (steep)
	{
		int temp = x0;
		int temp2 = x1;
		x0 = y0;
		y0 = temp;
		x1 = y1;
		y1 = temp2;
		dy = abs(y1 - y0);
		dx = abs(x1 - x0);
		m = dy;
	}

	if (x0 > x1)
	{
		int temp = x0;
		int temp2 = y0;
		x0 = x1;
		x1 = temp;
		y0 = y1;
		y1 = temp2;
	}

	float offset = 0;
	float threshold = dx * 2;
	int y = y0;

	for(int x = x0; x <= x1; x++)
	{
		offset += dy * 2;
		if (offset >= threshold)
		{
			int up = -1;
			if (y0 < y1) up = 1;
			y += up;
			threshold += 1 * dx * 2;
		}
		if(steep) pointLine(x, y);
		else pointLine(y, x);
	}
}