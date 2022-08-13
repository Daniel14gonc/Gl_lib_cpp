#include <string>
#include "obj.h"
#include "vector3.h"
#include "texture.h"

using namespace std;

class Render 
{
	private:
		int x0, y0;
		int widthV, heightV;
		int width;
		int height;
		float maxZ;
		float minZ;
		Texture* texture;
		unsigned char* clearColor;
		unsigned char* color;
		unsigned char*** frameBuffer;
		float** zBuffer;
		unsigned char* createFileHeader(int fileSize);
		unsigned char* createSizeHeader(int, int);
		void deleteMemory();
		int* calculatePosition(float, float);
		void pointLine(int, int);
		Vector3 transformVertex(vector<float>, int*, int*);
		float* barycentric(Vector3, Vector3, Vector3, Vector3);
		vector<Vector3> boundingBox(Vector3, Vector3, Vector3);
		float* cross(Vector3, Vector3);
		void writeZBuffer();

	public:
		Render();
		void startBuffer(int, int);
		void setBuffer(unsigned char***);
		int write(string path = "image.bmp");
		void clear();
		void point(float, float);
		void changeClearColor(float, float, float);
		void changeColor(float, float, float);
		void viewPort(int, int, int, int);
		void drawLine(float, float, float, float);
		void drawLine(int, int, int, int);
		void drawLine(Vector3, Vector3);
		void readObj(string);
		void triangle(Vector3, Vector3, Vector3);
		void triangle(vector<Vector3>);
		void triangle(vector<Vector3>, vector<Vector3>);
		void map();
		void setTexture(string);
};