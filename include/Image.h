#ifndef IMAGE_H
#define IMAGE_H

#include <GL/gl.h>
#include <vector>

#include "stb_image.h"
#include "include/Bindable.h"
#include "include/Debug.h"

class Image
{
private:
    int width, height;
    unsigned int format, size;
    unsigned char *data;

public:
    
    Image();
    Image(const char *filepath);
    unsigned char* LoadFromFile(const char *filepath);

    int GetWidth();
    int GetHeight();
    int GetSize();
    unsigned char* GetData();
    unsigned int GetFormat();
};

#endif // IMAGE_H
