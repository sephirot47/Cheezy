#include "include/Image.h"

Image::Image()
{
    width = height = format = size = 0;
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
        width = height = format = size = 0;
        DbgError("Error loading the texture '" << filepath << "', couldn't open/read the file.");
        return data;
    }
    if(n == 3) format = GL_RGB;
    else format = GL_RGBA;

    size = width * height * n * sizeof(float);

    return data;
}

int Image::GetWidth() const
{
    return width;
}

int Image::GetHeight() const
{
    return height;
}

int Image::GetSize() const
{
    return size;
}


unsigned char* Image::GetData() const
{
    return data;
}

unsigned int Image::GetFormat() const
{
    return format;
}

