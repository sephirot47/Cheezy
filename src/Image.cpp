#include "include/Image.h"

Image::Image()
{
    width = height = format = 0;
}

Image::Image(const char *filepath) : Image()
{
    LoadFromFile(filepath);
}

unsigned char* Image::LoadFromFile(const char *filepath)
{
    int n;
    data = stbi_load(filepath, &width, &height, &n, 0);
    if(data == 0)
    {
        width = height = format = 0;
        DbgError("Error loading the texture '" << filepath << "', couldn't open/read the file.");
        return data;
    }
    DbgLog("Img n: " << n);
    if(n == 3) format = GL_RGB;
    else format = GL_RGBA;

    return data;
}

int Image::GetWidth()
{
    return width;
}

int Image::GetHeight()
{
    return height;
}

unsigned char* Image::GetData()
{
    return data;
}

unsigned int Image::GetFormat()
{
    return format;
}

