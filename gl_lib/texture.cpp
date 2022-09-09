#include "texture.h"

Texture::Texture(string path)
{
    this->path = path;
    read();
}

void Texture::read()
{
    FILE* imageFile;
    string source = "../textures/" + path;
    char* src = new char[source.length()];
    
    for (int i = 0; i < source.length(); i++) src[i] = source.at(i);
	imageFile = fopen(src, "rb");

    // read the 54-byte header
    unsigned char info[54];
    fread(info, sizeof(unsigned char), 54, imageFile); 
    int headerSize = *(int*)&info[10];
    width = *(int*)&info[18];
    height = *(int*)&info[22];

    if (height < 0) height = height * -1;

    unsigned char info2[headerSize - 54];
    fread(info2, sizeof(unsigned char), headerSize - 54, imageFile); 

    pixels = new unsigned char**[height];
    for (int i = 0; i < height; i++)
    {
        pixels[i] = new unsigned char*[width];
    }

    // allocate 3 bytes per pixel
    int size = 3 * width * height;
    unsigned char* data = new unsigned char[size];

    // read the rest of the data at once
    fread(data, sizeof(unsigned char), size, imageFile); 
    fclose(imageFile);
    int x = 0;
    int y = 0;
    int i = 0;
	int paddingSize = (4 - (width * 3) % 4) % 4;
    for(i = 0; i < size; i += 3)
    {

        pixels[y][x] = new unsigned char[3];
        pixels[y][x][0] = data[i];
        pixels[y][x][1] = data[i + 1];
        pixels[y][x][2] = data[i + 2];
        //cout << i << endl;
        x += 1;
        if (x % width == 0)
        {
            y += 1;
            i += paddingSize;
        }
        x = x % width;
    }
}

unsigned char* Texture::getColor(float tx, float ty)
{
    int x = (int) tx * width;
    int y = (int) ty * height;

    return pixels[y][x];
}

unsigned char* Texture::getColorIntensity(float tx, float ty, float intensity)
{
    int x = (int) (tx * width);
    int y = (int) (ty * height);

    /*if (x >= width) x = width - 1;
    if (y >= height) y = height - 1;*/
    unsigned char b = (unsigned char)((float)pixels[y][x][0] * intensity);
    unsigned char g = (unsigned char)((float) pixels[y][x][1] * intensity);
    unsigned char r = (unsigned char)((float)pixels[y][x][2] * intensity);
    // cout << (float)pixels[y][x][2] << endl;
    // cout << (float)r << ' ' << (float)g << ' ' << (float)b << endl;
    unsigned char* color = new unsigned char[3];
    color[0] = b;
    color[1] = g;
    color[2] = r;

    return color;
}

unsigned char*** Texture::getPixels()
{
    return pixels;
}

int Texture::getWidth()
{
    return width;
}

int Texture::getHeight()
{
    return height;
}