#include <string>
#include <fstream>
#include <iostream>

using namespace std;

class Texture
{
    private:
        string path;
        int width;
        int height;
        unsigned char*** pixels;
        void read();

    public:
        Texture(string);
        unsigned char* getColor(float, float);
        unsigned char* getColorIntensity(float, float, float);
        unsigned char*** getPixels();
        int getWidth();
        int getHeight();
};