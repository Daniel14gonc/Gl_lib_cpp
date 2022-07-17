#include <iostream>
#include "gl.h"

using namespace std;


int main()
{
	glInit();
	glCreateWindow(500, 500);
	glViewPort(0, 0, 500, 500);
	glVertex(-0.3, 0);
	//glLine(-1, 0, 0.3, 0.3);
	glFinish();
	return 0;
}