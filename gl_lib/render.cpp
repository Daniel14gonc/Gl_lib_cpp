#include "render.h"
#include <iostream>
#include <fstream>
#include <cmath>
#include <vector>
#include <math.h>

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

	minZ = 9999;
	maxZ = -99999;
	l = new Vector3(0, 0, 1);
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

	zBuffer = new float*[height];

	x0 = 0;
	y0 = 0;
	widthV = w;
	heightV = h;
	clear();
}

void Render::setBuffer(unsigned char*** buffer)
{
	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < width; j++)
		{
			frameBuffer[i][j][2] = buffer[i][j][2];
			frameBuffer[i][j][1] = buffer[i][j][1];
			frameBuffer[i][j][0] = buffer[i][j][0];
		}
	}
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

	for (int i = 0; i < height; i++) 
	{
		zBuffer[i] = new float[width];
        for (int j = 0; j < width; j++) 
		{
        	zBuffer[i][j] = -9999;
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

int Render::write(string path)
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
	char* src = new char[path.length()];
    
    for (int i = 0; i < path.length(); i++) src[i] = path.at(i);
	imageFile = fopen(src, "wb");

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
	// writeZBuffer();
	// deleteMemory();
	return 0;
}

void Render::writeZBuffer()
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
	imageFile = fopen("zBuffer.bmp", "wb");

	// Write the headers into file.
	fwrite(fileHeader, 1, 14, imageFile);
	fwrite(fileSizeH, 1, 40, imageFile);

	unsigned char*** extraBuffer;
	extraBuffer = new unsigned char** [height];
	for(int i = 0; i < height; i++)
	{
		extraBuffer[i] = new unsigned char* [width];
	};

	for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
        	extraBuffer[i][j] = new unsigned char[3];
			if (zBuffer[i][j] == -9999) zBuffer[i][j] = minZ;
        	extraBuffer[i][j][2] = (unsigned char) (255 * ((zBuffer[i][j] - minZ) / (maxZ - minZ)));
        	extraBuffer[i][j][1] = (unsigned char) (255 * ((zBuffer[i][j] - minZ) / (maxZ - minZ)));
        	extraBuffer[i][j][0] = (unsigned char) (255 * ((zBuffer[i][j] - minZ) / (maxZ - minZ)));
        }
    }

	// Write the image into the file.
    for (int i = 0; i < height; i++) {
    	for(int j = 0; j < width; j++)
    	{
    		fwrite((unsigned char*)extraBuffer[j][i], 3, 1, imageFile);
    	}
    	fwrite(padding, 1, paddingSize, imageFile);
    }


	fclose(imageFile);
}

void Render::loadModelMatrix(float* scale, int* translate, float* rotation)
{
	Vector3 sc(scale[0], scale[1], scale[2]);
	Vector3 tr(translate[0], translate[1], translate[2]);
	Vector3 ro(rotation[0], rotation[1], rotation[2]);
	Matrix<4, 4> translation = {{{1, 0, 0, tr.getX()}, {0, 1, 0, tr.getY()}, {0, 0, 1, tr.getZ()}, {0, 0, 0, 1}}};
	Matrix<4, 4> scaling = {{{sc.getX(), 0, 0, 0}, {0, sc.getY(), 0, 0}, {0, 0, sc.getZ(), 0}, {0, 0, 0, 1}}};
	float a = ro.getX();
	Matrix<4, 4> xRotation = {{
		{1,      0,       0, 0},
		{0, cos(a), -sin(a), 0},
		{0, sin(a),  cos(a), 0},
		{0,      0,       0, 1}
	}};

	a = ro.getY();
	Matrix<4, 4> yRotation = {{
		{ cos(a), 0, sin(a), 0},
		{      0, 1,      0, 0},
		{-sin(a), 0, cos(a), 0},
		{      0,  0,     0, 1}
	}};

	a = ro.getZ();
	Matrix<4, 4> zRotation = {{
		{cos(a), -sin(a), 0, 0},
		{sin(a),  cos(a), 0, 0},
		{     0,       0, 1, 0},
		{     0,       0, 0, 1}
	}};
	
	Matrix<4, 4> rot = xRotation * yRotation * zRotation;
	model = translation * rot * scaling;
}

void Render::loadViewMatrix(Vector3 x, Vector3 y, Vector3 z, Vector3 center)
{
	Matrix<4, 4> mi = {{
		{x.getX(), x.getY(), x.getZ(), 0},
		{y.getX(), y.getY(), y.getZ(), 0},
		{z.getX(), z.getY(), z.getZ(), 0},
		{0, 0, 0, 1},
	}};

	Matrix<4, 4> O = {{
		{1, 0, 0, -center.getX()},
		{0, 1, 0, -center.getY()},
		{0, 0, 1, -center.getZ()},
		{0, 0, 0, 1}
	}};

	view = mi * O;
}

void Render::lookAt(float* e, float* c, float* u)
{
	Vector3 eye(e[0], e[1], e[2]);
	Vector3 center(c[0], c[1], c[2]);
	Vector3 up(u[0], u[1], u[2]);
	Vector3 z = (eye - center).normalized();
	Vector3 x = (up * z).normalized();
	Vector3 y = (z * x).normalized();
	loadViewMatrix(x, y, z, center);
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
	// cout << y << ' ' << width << endl;
	if (x < width && y < height && x  >= 0 && y >= 0)
	{
		frameBuffer[y][x][2] = color[2];
		frameBuffer[y][x][1] = color[1];
		frameBuffer[y][x][0] = color[0];
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
	int *coordinates2 = calculatePosition(c, d);
	int x1 = coordinates2[0];
	int y1 = coordinates2[1];
	// delete[] coordinates;

	float dy = abs(y1 - y0);
	float dx = abs(x1 - x0);

	bool steep = dy > dx;

	if (steep)
	{
		int temp = x0;
		x0 = y0;
		y0 = temp;
		int temp2 = y1;
		x1 = y1;
		y1 = temp2;
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

	dy = abs(y1 - y0);
	dx = abs(x1 - x0);

	float offset = 0;
	float threshold = dx * 2;
	int y = y0;
	cout << y0 << endl;

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

void Render::drawLine(int a, int b, int c, int d)
{
	int x0 = a;
	int y0 = b;
	int x1 = c;
	int y1 = d;

	float dy = abs(y1 - y0);
	float dx = abs(x1 - x0);

	bool steep = dy > dx;

	if (steep)
	{
		int temp = x0;
		x0 = y0;
		y0 = temp;
		int temp2 = x1;
		x1 = y1;
		y1 = temp2;
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

	dy = abs(y1 - y0);
	dx = abs(x1 - x0);

	float offset = 0;
	float threshold = dx * 2;
	int y = y0;

	for(int x = x0; x <= x1; x++)
	{
		offset += dy * 2;
		if (steep) pointLine(x, y);
		else pointLine(y, x);
		if (offset >= threshold)
		{
			int up = -1;
			if (y0 < y1) up = 1;
			y += up;
			threshold += 1 * dx * 2;
		}
	}
}

void Render::drawLine(Vector3 a, Vector3 b)
{
	int x0 = a.getX();
	int y0 = a.getY();
	int x1 = b.getX();
	int y1 = b.getY();

	float dy = abs(y1 - y0);
	float dx = abs(x1 - x0);

	bool steep = dy > dx;

	if (steep)
	{
		int temp = x0;
		x0 = y0;
		y0 = temp;
		int temp2 = x1;
		x1 = y1;
		y1 = temp2;
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

	dy = abs(y1 - y0);
	dx = abs(x1 - x0);

	float offset = 0;
	float threshold = dx * 2;
	int y = y0;
	// cout << x1 << endl;
	for(int x = x0; x <= x1; x++)
	{
		// cout << x << ' ' << y << endl;
		offset += dy * 2;
		if (steep) pointLine(y, x);
		else pointLine(x, y);
		if (offset >= threshold)
		{
			int up = -1;
			if (y0 < y1) up = 1;
			y += up;
			threshold += 1 * dx * 2;
		}
	}
}

void Render::readObj(string filename, float* scale, int* translate)
{
	Obj* obj = new Obj(filename);
	vector<vector<vector<int>>> faces = obj->getFaces();
	vector<vector<float>> vertex = obj->getVertex();
	vector<vector<float>> vt = obj->getVt();
	float scaleFactor[3] = {5, 5, 3};
	int translateFactor[3] = {700, 400, 0};
	for (vector<vector<int>> face : faces)
	{
		vector<Vector3> vec;
		vector<Vector3> vect;
		// cout << face.size() << endl;	
		for (int i = 0; i < face.size(); i++)
		{
			int f = face.at(i).at(0) - 1;
			Vector3 v = transformVertex(vertex.at(f), scale, translate);
			vec.push_back(v);
			int f1 = face.at(i).at(1) - 1;
			Vector3 vt1(vt.at(f1).at(0), vt.at(f1).at(1));
			vect.push_back(vt1);
		}

		if (face.size() == 4)
		{
			if (activeTexture != NULL)
			{
				activeVertexArray.push(vec.at(0));
				activeVertexArray.push(vec.at(1));
				activeVertexArray.push(vec.at(2));

				activeVertexArray.push(vect.at(0));
				activeVertexArray.push(vect.at(1));
				activeVertexArray.push(vect.at(2));

				activeVertexArray.push(vec.at(2));
				activeVertexArray.push(vec.at(3));
				activeVertexArray.push(vec.at(0));

				activeVertexArray.push(vect.at(2));
				activeVertexArray.push(vect.at(3));
				activeVertexArray.push(vect.at(0));
			}
			else
			{
				activeVertexArray.push(vec.at(0));
				activeVertexArray.push(vec.at(1));
				activeVertexArray.push(vec.at(2));
			}
		}

		if (face.size() == 3)
		{
			activeVertexArray.push(vec.at(0));
			activeVertexArray.push(vec.at(1));
			activeVertexArray.push(vec.at(2));
			if (activeTexture != NULL)
			{
				activeVertexArray.push(vect.at(0));
				activeVertexArray.push(vect.at(1));
				activeVertexArray.push(vect.at(2));
			}
		}
	}

	delete obj;
}

void Render::readObj(string filename)
{
	Obj* obj = new Obj(filename);
	vector<vector<vector<int>>> faces = obj->getFaces();
	vector<vector<float>> vertex = obj->getVertex();
	vector<vector<float>> vt = obj->getVt();
	// float scaleFactor[3] = {5, 5, 3};
	// int translateFactor[3] = {700, 400, 0};
	for (vector<vector<int>> face : faces)
	{
		vector<Vector3> vec;
		vector<Vector3> vect;
		// cout << face.size() << endl;	
		for (int i = 0; i < face.size(); i++)
		{
			int f = face.at(i).at(0) - 1;
			Vector3 v = transformVertex(vertex.at(f) /*scaleFactor, translateFactor*/);
			vec.push_back(v);
			int f1 = face.at(i).at(1) - 1;
			Vector3 vt1(vt.at(f1).at(0), vt.at(f1).at(1));
			vect.push_back(vt1);
		}

		if (face.size() == 4)
		{
			if (activeTexture != NULL)
			{
				activeVertexArray.push(vec.at(0));
				activeVertexArray.push(vec.at(1));
				activeVertexArray.push(vec.at(2));

				activeVertexArray.push(vect.at(0));
				activeVertexArray.push(vect.at(1));
				activeVertexArray.push(vect.at(2));
				// triangle(v1, vt2);

				// v1.clear(); vt2.clear();
				activeVertexArray.push(vec.at(2));
				activeVertexArray.push(vec.at(3));
				activeVertexArray.push(vec.at(0));

				activeVertexArray.push(vect.at(2));
				activeVertexArray.push(vect.at(3));
				activeVertexArray.push(vect.at(0));
			}
			else
			{
				activeVertexArray.push(vec.at(0));
				activeVertexArray.push(vec.at(1));
				activeVertexArray.push(vec.at(2));
			}
		}

		if (face.size() == 3)
		{
			activeVertexArray.push(vec.at(0));
			activeVertexArray.push(vec.at(1));
			activeVertexArray.push(vec.at(2));
			if (activeTexture != NULL)
			{
				activeVertexArray.push(vect.at(0));
				activeVertexArray.push(vect.at(1));
				activeVertexArray.push(vect.at(2));
			}
		}
	}

	delete obj;
}

Vector3 Render::transformVertex(vector<float> vec, float* scale, int* translate)
{
	Vector3 v (
		(vec.at(0) * scale[0]) + translate[0],
		(vec.at(1) * scale[1]) + translate[1],
		(vec.at(2) * scale[2]) + translate[2]
	);
	return v;
}

Vector3 Render::transformVertex(vector<float> vec)
{
	Vector4 augmentendVertex(
		vec.at(0),
		vec.at(1),
		vec.at(2),
		1
	);
	Vector4 transformedVertex = model * view * augmentendVertex;
	Vector3 v (
		transformedVertex.getX() / transformedVertex.getW(),
		transformedVertex.getY() / transformedVertex.getW(),
		transformedVertex.getZ() / transformedVertex.getW()
	);
	return v;
}

void Render::triangle(vector<Vector3> vertices, vector<Vector3> vt)
{
	Vector3 a = vertices.at(0);
	Vector3 b = vertices.at(1);
	Vector3 c = vertices.at(2);
	Vector3 tA = vt.at(0);
	Vector3 tB = vt.at(1);
	Vector3 tC = vt.at(2);

	color[2] = (unsigned char) (rand() % 255);
	color[1] = (unsigned char) (rand() % 255);
	color[0] = (unsigned char) (rand() % 255);

	Vector3 l = Vector3(0, 0, 1);
	Vector3 n = (b - a) * (c - a);
	float i = n.normalized().dot(l.normalized());
	if (i < 0)
		return;
	color[2] = (unsigned char) (int) 255 * i;
	color[1] = (unsigned char) (int) 255 * i;
	color[0] = (unsigned char) (int) 255 * i;

	int Acolor[3] = {255, 0, 0};
	int Bcolor[3] = {0, 255, 0};
	int Ccolor[3] = {0, 0, 255};

	vector<Vector3> vec = boundingBox(a, b, c);
	Vector3 min = vec.at(0);
	Vector3 max = vec.at(1);
	min.round();
	max.round();
	for (int x = (int) min.getX(); x <= (int) max.getX(); x++)
		for (int y = (int) min.getY(); y <= (int) max.getY(); y++)
		{
			float* temp = barycentric(a, b, c, Vector3(x, y));
			float w = temp[0]; float v = temp[1]; float u = temp[2];
			if (temp[0] >= 0 && temp[1] >= 0 && temp[2] >= 0)
			{
				float z = a.getZ() * temp[0] + b.getZ() * temp[1] + c.getZ() * temp[2];
				if (zBuffer[x][y] < z)
				{
					float tx = tA.getX() * w + tB.getX() * u + tC.getX() * v;
					float ty = tA.getY() * w + tB.getY() * u + tC.getY() * v;
					unsigned char* col = activeTexture->getColorIntensity(tx, ty, i);
					color[0] = col[0];
					color[1] = col[1];
					color[2] = col[2];
					zBuffer[x][y] = z;
					pointLine(x, y);
				}
				if (z < minZ)
					minZ = z;
				if (z > maxZ)
					maxZ = z;
			}

			/* color[2] = (unsigned char) Acolor[0] * temp[0] + Bcolor[0] * temp[1] + Ccolor[0] * temp[2];
			color[1] = (unsigned char) Acolor[1] * temp[0] + Bcolor[1] * temp[1] + Ccolor[1] * temp[2];
			color[0] = (unsigned char) Acolor[2] * temp[0] + Bcolor[2] * temp[1] + Ccolor[2] * temp[2]; */

			delete temp;
		}
}

void Render::draw()
{
	while (!activeVertexArray.empty()){
		triangle();
	}
}

void Render::triangle(vector<Vector3> vertices)
{
	Vector3 a = vertices.at(0);
	Vector3 b = vertices.at(1);
	Vector3 c = vertices.at(2);
	color[2] = (unsigned char) (rand() % 255);
	color[1] = (unsigned char) (rand() % 255);
	color[0] = (unsigned char) (rand() % 255);

	Vector3 l = Vector3(0, 0, 1);
	Vector3 n = (b - a) * (c - a);
	float i = n.normalized().dot(l.normalized());
	if (i < 0)
		return;
	color[2] = (unsigned char) (int) 255 * i;
	color[1] = (unsigned char) (int) 255 * i;
	color[0] = (unsigned char) (int) 255 * i;

	int Acolor[3] = {255, 0, 0};
	int Bcolor[3] = {0, 255, 0};
	int Ccolor[3] = {0, 0, 255};

	vector<Vector3> vec = boundingBox(a, b, c);
	Vector3 min = vec.at(0);
	Vector3 max = vec.at(1);
	min.round();
	max.round();
	for (int x = (int) min.getX(); x <= (int) max.getX(); x++)
		for (int y = (int) min.getY(); y <= (int) max.getY(); y++)
		{
			float* temp = barycentric(a, b, c, Vector3(x, y));
			if (temp[0] >= 0 && temp[1] >= 0 && temp[2] >= 0)
			{
				float z = a.getZ() * temp[0] + b.getZ() * temp[1] + c.getZ() * temp[2];
				if (zBuffer[x][y] < z)
				{
					zBuffer[x][y] = z;
					pointLine(x, y);
				}
				if (z < minZ)
					minZ = z;
				if (z > maxZ)
					maxZ = z;
			}

			/* color[2] = (unsigned char) Acolor[0] * temp[0] + Bcolor[0] * temp[1] + Ccolor[0] * temp[2];
			color[1] = (unsigned char) Acolor[1] * temp[0] + Bcolor[1] * temp[1] + Ccolor[1] * temp[2];
			color[0] = (unsigned char) Acolor[2] * temp[0] + Bcolor[2] * temp[1] + Ccolor[2] * temp[2]; */

			delete temp;
		}
}

void Render::triangle()
{
	Vector3 a = activeVertexArray.front();
	activeVertexArray.pop();
	Vector3 b = activeVertexArray.front();
	activeVertexArray.pop();
	Vector3 c = activeVertexArray.front();
	activeVertexArray.pop();
	float tAX = 0;
	float tAY = 0;
	float tBX = 0;
	float tBY = 0;
	float tCX = 0;
	float tCY = 0;
	if (activeTexture != NULL)
	{
		Vector3 tA = activeVertexArray.front();
		activeVertexArray.pop();
		Vector3 tB = activeVertexArray.front();
		activeVertexArray.pop();
		Vector3 tC = activeVertexArray.front();
		activeVertexArray.pop();

		tAX = tA.getX();
		tAY = tA.getY();
		tBX = tB.getX();
		tBY = tB.getY();
		tCX = tC.getX();
		tCY = tC.getY();
	}

	color[2] = (unsigned char) (rand() % 255);
	color[1] = (unsigned char) (rand() % 255);
	color[0] = (unsigned char) (rand() % 255);
	
	Vector3 n = (b - a) * (c - a);
	float i = n.normalized().dot(l->normalized());
	if (i < 0) 
		return;
	color[2] = (unsigned char) (int) 255 * i;
	color[1] = (unsigned char) (int) 255 * i;
	color[0] = (unsigned char) (int) 255 * i;

	int Acolor[3] = {255, 0, 0};
	int Bcolor[3] = {0, 255, 0};
	int Ccolor[3] = {0, 0, 255};

	vector<Vector3> vec = boundingBox(a, b, c);
	Vector3 min = vec.at(0);
	Vector3 max = vec.at(1);
	min.round();
	max.round();
	for (int x = (int) min.getX(); x <= (int) max.getX(); x++)
		for (int y = (int) min.getY(); y <= (int) max.getY(); y++)
		{
			float* temp = barycentric(a, b, c, Vector3(x, y));
			float w = temp[0]; float v = temp[1]; float u = temp[2];
			if (temp[0] >= 0 && temp[1] >= 0 && temp[2] >= 0)
			{
				float z = a.getZ() * temp[0] + b.getZ() * temp[1] + c.getZ() * temp[2];
				if (zBuffer[x][y] < z)
				{
					if (activeTexture != NULL)
					{
						float tx = tAX * w + tBX * u + tCX * v;
						float ty = tAY * w + tBY * u + tCY * v;
						unsigned char* col = activeTexture->getColorIntensity(tx, ty, i);
						color[0] = col[0];
						color[1] = col[1];
						color[2] = col[2];
					}
					zBuffer[x][y] = z;
					pointLine(x, y);
				}
				if (z < minZ)
					minZ = z;
				if (z > maxZ)
					maxZ = z;
			}

			delete temp;
		}
}

void Render::triangle(Vector3 a, Vector3 b, Vector3 c)
{
	color[2] = (unsigned char) (rand() % 255);
	color[1] = (unsigned char) (rand() % 255);
	color[0] = (unsigned char) (rand() % 255);

	Vector3 l = Vector3(0, 0, 1);
	Vector3 n = (b - a) * (c - a);
	float i = n.normalized().dot(l.normalized());
	if (i < 0)
		return;
	color[2] = (unsigned char) (int) 255 * i;
	color[1] = (unsigned char) (int) 255 * i;
	color[0] = (unsigned char) (int) 255 * i;

	int Acolor[3] = {255, 0, 0};
	int Bcolor[3] = {0, 255, 0};
	int Ccolor[3] = {0, 0, 255};

	vector<Vector3> vec = boundingBox(a, b, c);
	Vector3 min = vec.at(0);
	Vector3 max = vec.at(1);
	min.round();
	max.round();
	for (int x = (int) min.getX(); x <= (int) max.getX(); x++)
		for (int y = (int) min.getY(); y <= (int) max.getY(); y++)
		{
			float* temp = barycentric(a, b, c, Vector3(x, y));
			if (temp[0] >= 0 && temp[1] >= 0 && temp[2] >= 0)
			{
				float z = a.getZ() * temp[0] + b.getZ() * temp[1] + c.getZ() * temp[2];
				if (zBuffer[x][y] < z)
				{
					zBuffer[x][y] = z;
					pointLine(x, y);
				}
				if (z < minZ)
					minZ = z;
				if (z > maxZ)
					maxZ = z;
			}

			/* color[2] = (unsigned char) Acolor[0] * temp[0] + Bcolor[0] * temp[1] + Ccolor[0] * temp[2];
			color[1] = (unsigned char) Acolor[1] * temp[0] + Bcolor[1] * temp[1] + Ccolor[1] * temp[2];
			color[0] = (unsigned char) Acolor[2] * temp[0] + Bcolor[2] * temp[1] + Ccolor[2] * temp[2]; */

			delete temp;
		}
}

vector<Vector3> Render::boundingBox(Vector3 A, Vector3 B, Vector3 C)
{
	float coords[3][2] = {{A.getX(), A.getY()}, {B.getX(), B.getY()}, {C.getX(), C.getY()}};

	float xmin = 999999.0f;
	float xmax= -999999.0f;
	float ymin = 999999.0f;
	float ymax = -999999.0f;

	for (int i = 0; i < 3; i++)
	{
		if (coords[i][0] < xmin)
			xmin = coords[i][0];
		if (coords[i][0] > xmax)
			xmax = coords[i][0];
		if (coords[i][1] < ymin)
			ymin = coords[i][1];
		if (coords[i][1] > ymax)
			ymax = coords[i][1];
	}

	vector<Vector3> res;
	res.push_back(Vector3(xmin, ymin));
	res.push_back(Vector3(xmax, ymax));
	return res;
}

float* Render::cross(Vector3 a, Vector3 b)
{
	float* res = new float[3];
	res[0] = a.getY() * b.getZ() - a.getZ() * b.getY();
	res[1] = a.getZ() * b.getX() - a.getX() * b.getZ();
	res[2] = a.getX() * b.getY() - a.getY() * b.getX();
	return res;
}

float* Render::barycentric(Vector3 A, Vector3 B, Vector3 C, Vector3 P)
{
	float* crs = cross(
		Vector3(B.getX() - A.getX(), C.getX() - A.getX(), A.getX() - P.getX()),
		Vector3(B.getY() - A.getY(), C.getY() - A.getY(), A.getY() - P.getY())
	);

	float u = crs[0] / crs[2];
	float v = crs[1] / crs[2];
	float w = 1.0f - (u + v);

	delete crs;

	float* res = new float[3];
	res[0] = w;
	res[1] = v;
	res[2] = u;
	return res;
}

void Render::setTexture(string path)
{
	activeTexture = new Texture(path);
}

void Render::map(string path)
{
	Texture* texture = new Texture(path + ".bmp");
	startBuffer(texture->getWidth(), texture->getHeight());
    Obj obj(path + ".obj");
    vector<vector<vector<int>>> faces = obj.getFaces();
    vector<vector<float>> vts = obj.getVt();
    changeColor(1, 1, 1);
    setBuffer(texture->getPixels());
    for (vector<vector<int>> f : faces)
    {
		if (f.size() == 4)
		{
			int f1 = f.at(0).at(1) - 1;
            int f2 = f.at(1).at(1) - 1;
            int f3 = f.at(2).at(1) - 1;
			int f4 = f.at(3).at(1) - 1;

            Vector3 vt1(vts.at(f1).at(0) * width, vts.at(f1).at(1) * height);
            Vector3 vt2(vts.at(f2).at(0) * width, vts.at(f2).at(1) * height);
            Vector3 vt3(vts.at(f3).at(0) * width, vts.at(f3).at(1) * height);
			Vector3 vt4(vts.at(f4).at(0) * width, vts.at(f3).at(1) * height);

            drawLine(vt1, vt2);
            drawLine(vt2, vt1);
            drawLine(vt3, vt1);

			drawLine(vt2, vt3);
            drawLine(vt3, vt4);
            drawLine(vt4, vt2);
		}
        if(f.size() == 3)
        {
            int f1 = f.at(0).at(1) - 1;
            int f2 = f.at(1).at(1) - 1;
            int f3 = f.at(2).at(1) - 1;

            Vector3 vt1(vts.at(f1).at(0) * width, vts.at(f1).at(1) * height);
            Vector3 vt2(vts.at(f2).at(0) * width, vts.at(f2).at(1) * height);
            Vector3 vt3(vts.at(f3).at(0) * width, vts.at(f3).at(1) * height);

            drawLine(vt1, vt2);
            drawLine(vt2, vt1);
            drawLine(vt3, vt1);
        }
    }
    write("map.bmp");
	delete texture;
}

/*
vector<int> Render::transformVertex(vector<float> vec, int* scale, int* translate)
{
	Vector3 v (
		(vec.at(0) * scale[0]) + translate[0],
		(vec.at(1) * scale[1]) + translate[1]
	)
	
	vector<int> temp;
	temp.push_back((int)((vec.at(0) * scale[0]) + translate[0]));
	temp.push_back((int)((vec.at(1) * scale[1]) + translate[1]));
	
	return temp;
}*/

/*void Render::triangle(Vector3 a, Vector3 b, Vector3 c)
{
	drawLine(a, b);
	drawLine(b, c);
	drawLine(c, a);

	a.round();
	b.round();
	c.round();

	color[2] = (unsigned char) (rand() % 255);
	color[1] = (unsigned char) (rand() % 255);
	color[0] = (unsigned char) (rand() % 255);

	if (a.getY() > b.getY())
	{
		Vector3 temp = a;
		a = b;
		b = temp;
	}

	if(a.getY() > c.getY())
	{
		Vector3 temp = a;
		a = c;
		c = temp;
	}

	if(b.getY() > c.getY())
	{
		Vector3 temp = b;
		b = c;
		c = temp;
	}

	float dx_ac = c.getX() - a.getX();
	float dy_ac = c.getY() - a.getY();
	if (dy_ac == 0)
		return;
	float m_ac = dx_ac / dy_ac;

	float dx_ab = b.getX() - a.getX();
	float dy_ab = b.getY() - a.getY();
	if (dy_ab != 0)
	{
		float m_ab = dx_ab / dy_ab;
		for (int y = (int) a.getY(); y <= (int) b.getY(); y++)
		{
			float x0 = a.getX() - m_ac * (a.getY() - y);
			float xf = a.getX() - m_ab * (a.getY() - y);
			if (x0 > xf)
			{
				float temp = x0;
				x0 = xf;
				xf = temp;
			}
			for (int x = (int) x0; x <= (int) xf; x++)
			{
				pointLine(y, x);
			}
		}
	}

	float dx_bc = c.getX() - b.getX();
	float dy_bc = c.getY() - b.getY();
	if (dy_bc != 0)
	{
		float m_bc = dx_bc / dy_bc;
		for (int y = (int) b.getY(); y < (int) c.getY(); y++)
		{
			float x0 = a.getX() - m_ac * (a.getY() - y);
			float xf = b.getX() - m_bc * (b.getY() - y);
			if (x0 > xf)
			{
				float temp = x0;
				x0 = xf;
				xf = temp;
			}
			for (int x = (int) x0; x <= (int) xf; x++)
			{
				pointLine(y, x);
			}
		}
	}
}*/

