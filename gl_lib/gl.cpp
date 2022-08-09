#include "gl.h"
#include <iostream>

Render* render;
unsigned char*** frameBuffer;
int height, width;

void glInit()
{
	height = 0; width = 0;
	render = new Render();
}

void glCreateWindow(int h, int w)
{
	render->startBuffer(h, w);
}

void glClear()
{
	render->clear();
}

void glFinish()
{
	render->write();
}

void glVertex(float x, float y)
{
	render->point(x, y);
}

void glClearColor(float r, float g, float b)
{
	render->changeClearColor(r, g, b);
}

void glColor(float r, float g, float b)
{
	render->changeColor(r, g, b);
}

void glViewPort(int x, int y, int width, int height)
{
	render->viewPort(x, y, width, height);
}

void glLine(float x0, float y0, float x1, float y1)
{
	render->drawLine(x0, y0, x1, y1);
}

void glObject(string filename)
{
	render->readObj(filename);
}

void glLine(Vector3 a, Vector3 b)
{
	render->drawLine(a, b);
}

void glTriangle(Vector3 a, Vector3 b, Vector3 c)
{
	render->triangle(a, b, c);
}