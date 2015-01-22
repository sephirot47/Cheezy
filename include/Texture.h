#ifndef TEXTURE_H
#define TEXTURE_H

#include <GL/gl.h>
#include <vector>
#include "stb_image.h"
#include "include/Image.h"
#include "include/Bindable.h"

#include "include/Debug.h"

#define CZ_FILTER_POINT GL_NEAREST
#define CZ_FILTER_BILINEAR GL_LINEAR

#define CZ_WRAP_CLAMP GL_CLAMP
#define CZ_WRAP_REPEAT GL_REPEAT

using namespace std;

enum FilterMode
{
    LinearFilter = GL_LINEAR,
    PointFilter = GL_NEAREST
};

enum WrapMode
{
    ClampWrap = GL_CLAMP,
    RepeatWrap = GL_REPEAT
};

class Texture : public Bindable
{
private:

    unsigned int id, format, size;
    int width, height, n;

public:

    unsigned char *data;

    Texture();
    Texture(Texture &tex);
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
