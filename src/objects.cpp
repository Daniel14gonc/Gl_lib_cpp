#include <iostream>
#include "gl.h"

using namespace std;


int main()
{
	glInit();
	glCreateWindow(1500, 1500);
	glObject("spider.obj");
	glFinish();
	return 0;
}