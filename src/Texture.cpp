#include "Texture.h"

Texture::Texture()
{
    glGenTextures(1, &id);
}

Texture::Texture(const char *filepath) : Texture()
{
    LoadFromFile(filepath);
}

bool Texture::LoadFromFile(const char *filepath)
{
    data = stbi_load(filepath, &width, &height, &n, 0);
    if(data == 0){ DbgError("Error loading the texture '" << filepath << "', couldn't open/read the file."); return false; };

    DBG_ASSERT_GL_RET_MSG( glBindTexture(GL_TEXTURE_2D, id), "Couldn't bind on loading the texture '" << filepath << "'");
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    //glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, wrapMode);
    //glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, wrapMode);
    DBG_ASSERT_GL_RET_MSG( glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data), "Couldn't load the texture '" << filepath << "'");
    glBindTexture(GL_TEXTURE_2D, 0);

    return true;
}

unsigned int Texture::GetId()
{
    return id;
}

void Texture::Bind()
{
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, id);

   // glUniform1i(0, id);
}

void Texture::UnBind()
{
    glBindTexture(GL_TEXTURE_2D, 0);
}
