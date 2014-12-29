#ifndef TEXTURE_H
#define TEXTURE_H

#include <GL/gl.h>
#include <vector>
#include "stb_image.h"
#include "include/Image.h"
#include "include/Bindable.h"

#include "include/Debug.h"

using namespace std;

class Texture : public Bindable
{
private:

    unsigned int id;
    unsigned int format;

public:

    int width, height, n;
    unsigned char *data;

    Texture();
    Texture(const char *filepath);
    virtual ~Texture();

    bool LoadFromFile(const char *filepath);

    unsigned int GetId();
    unsigned int GetFormat();


    void Bind();
    void UnBind();
};

#endif // TEXTURE_H
