#include <iostream>
#include "gl.h"

using namespace std;

bool isInLine(int a, int b, int c, int d, int x, int y)
{
	cout << x << ' ' << y;
	float m = (d - b) / (b - a);
	float x0 = d - (m * c);
	float res = m*x + x0;
	if (res == y)
		return true;
	return false;
}

bool isInPolygon(int size, int points[][2], int x, int y)
{	
	int i, j;
	bool c = false;
	j = size - 1;
	for (i = 0; i < size; i++) 
	{
		if (x == points[i][0] && y == points[i][1])
			return true;
		if ((points[i][1] > y) != (points[j][1] > y))
		{
			float m = (x-points[i][0])*(points[j][1]-points[i][1])-(points[j][0]-points[i][0])*(y-points[i][1]);
			if (m == 0.0){
				return true;
			}
			if ((m < 0) != (points[j][1] < points[i][1]))
				c = !c;
		}
		j = i;
	}
	return c;
}

int greatestY(int size, int points[][2])
{
	int res = points[0][1]; 
	for (int i = 1; i < size; i++)
	{
		if (res < points[i][1])
			res = points[i][1];
	}
	return res;
}

int lowestY(int size, int points[][2])
{
	int res = points[0][1]; 
	for (int i = 1; i < size; i++)
	{
		if (res > points[i][1])
			res = points[i][1];
	}
	return res;
}

int greatestX(int size, int points[][2])
{
	int res = points[0][0]; 
	for (int i = 1; i < size; i++)
	{
		if (res < points[i][0])
			res = points[i][0];
	}
	return res;
}

int lowestX(int size, int points[][2])
{
	int res = points[0][0]; 
	for (int i = 1; i < size; i++)
	{
		if (res > points[i][0])
			res = points[i][0];
	}
	return res;
}

void fillPolygon(int size, int points[][2])
{
	int i, j;
	int lY = lowestY(size, points);
	int gY = greatestY(size, points);
	int lX = lowestX(size, points);
	int gX = greatestX(size, points);
	for (int k = 0; k < 680000; k++)
	{
		i = lX + (rand() % (gX - lX + 1 ));
		j = lY + (rand() % (gY - lY + 1 ));
		if(isInPolygon(size, points, i, j))
			glVertex((i / 800.0f) * 2 - 1, ((j / 800.0f) * 2) - 1);
		if(isInPolygon(size, points, i+1, j))
			glVertex((i+1 / 800.0f) * 2 - 1, ((j / 800.0f) * 2) - 1);
		if(isInPolygon(size, points, i-1, j))
			glVertex((i-1 / 800.0f) * 2 - 1, ((j / 800.0f) * 2) - 1);
		if(isInPolygon(size, points, i, j+1))
			glVertex((i / 800.0f) * 2 - 1, ((j+1 / 800.0f) * 2) - 1);
		if(isInPolygon(size, points, i, j-1))
			glVertex((i / 800.0f) * 2 - 1, ((j-1 / 800.0f) * 2) - 1);
	}
}

int main()
{
	cout << 25 + ( std::rand() % ( 63 - 25 + 1 ) ) << endl;
	glInit();
	glCreateWindow(800, 800);

	// Estrella
	int pol1[10][2] = {
		{165, 380},
		{185, 360},
		{180, 330},
		{207, 345},
		{233, 330},
		{230, 360},
		{250, 380},
		{220, 385},
		{205, 410},
		{193, 383}
	};

	glColor(1, 1, 0.2);
	fillPolygon(10, pol1);

	// Rombo
	int pol2[4][2] = {{321, 335}, {288, 286}, {339, 251}, {374, 302}};

	glColor(0, 0, 1);
	fillPolygon(4, pol2);

	// Triangulo
	int pol3[3][2] = {{377, 249}, {411, 197}, {436, 249}};

	glColor(0, 0.5, 0);
	fillPolygon(3, pol3);

	// Tetera
	int pol4[18][2] = {
		{413, 177}, {448, 159}, 
		{502, 88}, {553, 53}, 
		{535, 36}, {676, 37}, 
		{660, 52}, {750, 145}, 
		{761, 179}, {672, 192}, 
		{659, 214}, {615, 214}, 
		{632, 230}, {580, 230}, 
		{597, 215}, {552, 214}, 
		{517, 144}, {466, 180}
	};

	glColor(0.7, 0, 0);
	fillPolygon(18, pol4);

	// Hoyo tetera
	int pol5[4][2] = {
		{682, 175}, {708, 120}, 
		{735, 148}, {739, 170}
	};

	glColor(0.9, 0, 0);
	fillPolygon(4, pol5);

	glFinish();
	return 0;
}