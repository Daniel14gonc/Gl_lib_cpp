#include <string>

class Render 
{
	private:
		int width;
		int height;
		//unsigned char*** frameBuffer;
		unsigned char* createFileHeader(int fileSize);
		unsigned char* createSizeHeader(int, int);
		int clear(unsigned char*);
		//int writeHelper();
		int frameBufferPrep();
		int deleteMemory();

	public:
		void startBuffer(int, int);
		int write(unsigned char***, int, int);
};