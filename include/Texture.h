#ifndef TEXTURE_H
#define TEXTURE_H

#include <GL/gl.h>
#include <vector>
#include "stb_image.h"
#include "Bindable.h"
#include "Color.h"
#include "Debug.h"

using namespace std;

class Texture : public Bindable
{
private:

    unsigned int id;

public:

    int width, height, n;
    unsigned char *data;

    Texture();
    Texture(const char *filepath);
    bool LoadFromFile(const char *filepath);

    unsigned int GetId();

    void Bind();
    void UnBind();
};

#endif // TEXTURE_H
