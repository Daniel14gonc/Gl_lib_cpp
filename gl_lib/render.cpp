#include "render.h"
#include <iostream>
#include <fstream>

using namespace std;

int Render::write(unsigned char*** frameBuffer, int width, int height)
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