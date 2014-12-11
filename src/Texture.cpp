#include "Texture.h"

Texture::Texture()
{
    glGenTextures(1, &texId);
}

Texture::Texture(const char *filepath) : Texture()
{
    LoadFromFile(filepath);
}

bool Texture::LoadFromFile(const char *filepath)
{
    data = stbi_load(filepath, &width, &height, &n, 0);
    if(data == 0){ DbgError("Error loading the texure " << filepath); return false; };
    DbgLog("Texture loaded!");
    return true;
}
