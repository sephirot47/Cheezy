#ifndef TEXTURE_H
#define TEXTURE_H

#include <GL/gl.h>
#include "stb_image.h"
#include "Color.h"
#include "Debug.h"

class Texture
{

public:

    unsigned int texId;
    int width, height, n;
    unsigned char *data;

    Texture();
    Texture(const char *filepath);
    bool LoadFromFile(const char *filepath);
};

#endif // TEXTURE_H
