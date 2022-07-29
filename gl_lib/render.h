#include <string>
#include "obj.h"

using namespace std;

class Render 
{
	private:
		int x0, y0;
		int widthV, heightV;
		int width;
		int height;
		unsigned char* clearColor;
		unsigned char* color;
		unsigned char*** frameBuffer;
		unsigned char* createFileHeader(int fileSize);
		unsigned char* createSizeHeader(int, int);
		void deleteMemory();
		int* calculatePosition(float, float);
		void pointLine(int, int);
		vector<int> transformVertex(vector<float>, int*, int*);

	public:
		Render();
		void startBuffer(int, int);
		int write();
		void clear();
		void point(float, float);
		void changeClearColor(float, float, float);
		void changeColor(float, float, float);
		void viewPort(int, int, int, int);
		void drawLine(float, float, float, float);
		void drawLine(int, int, int, int);
		void readObj(string);
};