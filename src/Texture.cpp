#include "include/Texture.h"

Texture::Texture()
{
    glGenTextures(1, &id);
    size = 0;
}

Texture::Texture(Texture &tex)
{
    glGenTextures(1, &id);
    width = tex.width;
    height = tex.height;
    n = tex.n;
    format = tex.format;
    size = tex.size;
    memcpy(data, tex.data, tex.size);
}

Texture::~Texture()
{
    if(data) delete data;
}

Texture::Texture(const char *filepath) : Texture()
{
    LoadFromFile(filepath);
}

bool Texture::LoadFromFile(const char *filepath)
{
    Image img(filepath);
    if(img.GetWidth() == 0) return false; //cant load image
    data = img.GetData();
    size = img.GetSize();

    glBindTexture(GL_TEXTURE_2D, id);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_REPEAT);

    DBG_ASSERT_GL_RET_MSG( glTexImage2D(GL_TEXTURE_2D, 0,
                                        img.GetFormat(), img.GetWidth(), img.GetHeight(), 0,
                                        img.GetFormat(), GL_UNSIGNED_BYTE, data),
                                        "Couldn't load the texture '" << filepath << "'");
    glBindTexture(GL_TEXTURE_2D, 0);
    return true;
}

void Texture::SetWrapMode(WrapMode wrapMode)
{
    glBindTexture(GL_TEXTURE_2D, id);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, wrapMode);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, wrapMode);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_R, wrapMode);
    glBindTexture(GL_TEXTURE_2D, 0);
}

void Texture::SetFilterMode(FilterMode filterMode)
{
    glBindTexture(GL_TEXTURE_2D, id);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, filterMode);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, filterMode);
    glBindTexture(GL_TEXTURE_2D, 0);
}

unsigned int Texture::GetId() const { return id; }
unsigned int Texture::GetFormat() const{ return format; }
unsigned int Texture::GetSize() const { return size; }

void Texture::Bind() const
{
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, id);
}

void Texture::UnBind() const { glBindTexture(GL_TEXTURE_2D, 0); }

int Texture::GetWidth() const
{
    return width;
}

int Texture::GetHeight() const
{
    return height;
}

unsigned char * const Texture::GetRawData()
{
    return data;
}

