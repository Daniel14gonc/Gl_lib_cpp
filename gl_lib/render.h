#include <string>
#include "obj.h"
#include "vector3.h"
#include "texture.h"
#include <queue>
#include <matrix.hpp>
#include "simplex.h"

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
		Texture* activeTexture;
		Vector3* l;
		unsigned char* clearColor;
		unsigned char* color;
		unsigned char*** frameBuffer;
		float** zBuffer;
		unsigned char* createFileHeader(int fileSize);
		unsigned char* createSizeHeader(int, int);
		void deleteMemory();
		int* calculatePosition(float, float);
		void pointLine(int, int);
		Vector3 transformVertex(vector<float>, float*, int*);
		Vector3 transformVertex(vector<float>);
		float* barycentric(Vector3, Vector3, Vector3, Vector3);
		vector<Vector3> boundingBox(Vector3, Vector3, Vector3);
		float* cross(Vector3, Vector3);
		void writeZBuffer();
		queue<Vector3> activeVertexArray;
		Matrix<4, 4> model;
		Matrix<4, 4> view;
		Matrix<4, 4> projection;
		Matrix<4, 4> viewport;
		void loadViewMatrix(Vector3, Vector3, Vector3, Vector3);
		bool activeShader;
		SimplexNoise s;

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
		void readObj(string, float*, int*);
		void readObj(string);
		void triangle(Vector3, Vector3, Vector3);
		void triangle(vector<Vector3>);
		void triangle(vector<Vector3>, vector<Vector3>);
		void triangle();

		template<class Types>
		unsigned char* shader(initializer_list<Types> list);

		unsigned char* shader(vector<Vector3> vertices, vector<Vector3> textureCoords, vector<Vector3> normals, float* bar, Vector3*);
		unsigned char* shader(int , int);
		unsigned char* shader(int , int, vector<Vector3> normals, float* bar, Vector3* l);
		void map(string path);
		void setTexture(string);
		void draw();
		void loadModelMatrix(float*, float*, float*);
		void lookAt(float*, float*, float*);
		void loadProjectionMatrix();
		void loadViewportMatrix();
		void activate();
};