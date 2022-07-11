#include "render.h"

class MyGl
{
	private:
		Render render;
		unsigned char*** frameBuffer;
		int height, width;
		void deleteMemory();

	public:
		void glInit();
		void glCreateWindow(int, int);
		void glViewPort(int, int, int, int);
		void glCLear();
		void glClearColor();
		void glVertex(float, float);
		void glColor(float, float, float);
		void glFinish();
};