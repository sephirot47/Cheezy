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

    unsigned int id, format, size;
    int width, height, n;

public:

    enum FilterMode {
        FilterLinear = GL_LINEAR,
        FilterPoint = GL_NEAREST
    };

    enum WrapMode {
        WrapClamp = GL_CLAMP,
        WrapRepeat = GL_REPEAT
    };

    unsigned char *data;

    Texture();
    Texture(const Texture &tex);
    Texture(const char *filepath);
    virtual ~Texture();

    bool LoadFromFile(const char *filepath);

    void SetWrapMode(WrapMode wrapMode);
    void SetFilterMode(FilterMode filterMode);

    unsigned int GetId() const;
    unsigned int GetFormat() const;
    unsigned int GetSize() const;

    void Bind() const;
    void UnBind() const;

    int GetWidth() const;
    int GetHeight() const;

    unsigned char * const GetRawData();
};

#endif // TEXTURE_H
