#ifndef SHADER_H
#define SHADER_H

#define GL_GLEXT_PROTOTYPES //Needed to include glext.h, to use glbuffers

#include <GL/gl.h>
#include <GL/glext.h>
#include <vector>
#include "Debug.h"
#include "Component.h"
#include "Vector3.h"
#include "Vector2.h"

#define CZ_VERTEX_SHADER GL_VERTEX_SHADER
#define CZ_FRAGMENT_SHADER GL_FRAGMENT_SHADER

#define CZ_MAX_SHADER_ERROR_LOG_SIZE 2056
using namespace std;

class Shader
{
private:

    char* srcCode;
    int srcCodeLength;
    unsigned int shaderId;
    unsigned int type; //Vertex o fragment

public:

    Shader();

    ///\brief Creates a shader of type shaderType
    ///       shaderType can be CZ_VERTEX_SHADER or CZ_FRAGMENT_SHADER
    Shader(unsigned int shaderType);

    ///\brief Loads a shader from a file, compiles it and binds it to openGL
    ///       If something went wrong, returns false. Otherwise, returns true.
    bool LoadFromFile(const char *filepath);

    ///\brief Returns the shader id.
    ///       If the shader hasn't been loaded yet from a file, returns -1.
    int GetShaderId();
};

#endif // SHADER_H
