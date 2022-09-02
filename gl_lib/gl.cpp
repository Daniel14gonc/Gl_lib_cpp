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
	render->loadViewportMatrix();
}

void glLine(float x0, float y0, float x1, float y1)
{
	render->drawLine(x0, y0, x1, y1);
}

void glObject(string filename)
{
	render->readObj(filename);
}

void glObject(string filename, float* scale, int* translate)
{
	render->readObj(filename, scale, translate);
}

void glLine(Vector3 a, Vector3 b)
{
	render->drawLine(a, b);
}

void glTriangle(Vector3 a, Vector3 b, Vector3 c)
{
	render->triangle(a, b, c);
}

void glMap(string path)
{
	render->map(path);
}

void glTexture(string path)
{
	render->setTexture(path);
}

void glDraw()
{
	render->draw();
}

void glLoadMatrix(float* scale, float* translate, float* rotate)
{
	render->loadModelMatrix(scale, translate, rotate);
}

void glEye(float* eye, float* center, float* up)
{
	render->lookAt(eye, center, up);
}