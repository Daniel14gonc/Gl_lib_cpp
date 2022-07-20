#include <string>

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

		// Helper method for writing file header to bmp file.
		unsigned char* createFileHeader(int fileSize);

		// Helper method for writing size header to bmp file.
		unsigned char* createSizeHeader(int, int);

		// Method for handling memory.
		void deleteMemory();

		// Method for transforming to pixels from NDC.
		int* calculatePosition(float, float);

		// Method for writing the pixels from the line to streambuffer.
		void pointLine(int, int);

	public:
		Render();

		// Method for initializing the buffer with user dimensions.
		void startBuffer(int, int);

		// Method for writing to a bmp file, the stram buffer.
		int write();

		// Method for clearing the streambuffer.
		void clear();

		//Method fro drawing a point.
		void point(float, float);

		// Method for changing the color used for clearing the streambuffer.
		void changeClearColor(float, float, float);

		// Method for changing the color when painting.
		void changeColor(float, float, float);

		// Method for setting the viewport in which everything will be drawn.
		void viewPort(int, int, int, int);

		// Method for drawing a line.
		void drawLine(float, float, float, float);
};