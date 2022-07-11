#include <iostream>
#include "MyGl.h"

using namespace std;

int main()
{
	MyGl myGl;
	myGl.glCreateWindow(1024, 1024);
	for(int i = 0; i < 1024; i++)
	{
		myGl.glVertex(i, i);
	}
	myGl.glFinish();
	return 0;
}