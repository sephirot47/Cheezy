#ifndef SHADER_H
#define SHADER_H

#define GL_GLEXT_PROTOTYPES //Needed to include glext.h, to use glbuffers

#include <GL/gl.h>
#include <GL/glext.h>
#include <string>
#include <vector>
#include "include/Debug.h"
#include "include/Component.h"
#include "include/Bindable.h"

enum ShaderType
{
    VertexShader = GL_VERTEX_SHADER,
    FragmentShader = GL_FRAGMENT_SHADER
};

#define CZ_MAX_SHADER_ERROR_LOG_SIZE 2056

using namespace std;

class Shader
{
private:

    string srcCode, filepath;
    unsigned int shaderId;
    ShaderType type;

public:

    Shader();
    Shader(const Shader &shader);
    Shader& operator=(const Shader &shader);
    virtual ~Shader();

    static void GetDefaultVertex(Shader &s);
    static void GetDefaultFragment(Shader &s);

    ///\brief Creates a shader of type shaderType
    ///       shaderType can be CZ_VERTEX_SHADER or CZ_FRAGMENT_SHADER
    Shader(ShaderType shaderType);

    ///\brief Creates a shader of type shaderType and calls LoadFromFile(filepath) directly
    ///       shaderType can be CZ_VERTEX_SHADER or CZ_FRAGMENT_SHADER
    Shader(ShaderType shaderType, string filepath);

    ///\brief Loads a shader from a file, compiles it and binds it to openGL
    ///       If something went wrong, returns false. Otherwise, returns true.
    bool LoadFromFile(string filepath);

    bool LoadFromSourceCode(string srcCode);

    ///\brief Returns the shader id.
    ///       If the shader hasn't been loaded yet from a file, returns -1.
    int GetId() const;

    ///\brief Returns the shader type.
    ///       It can be CZ_VERTEX_SHADER or CZ_FRAGMENT_SHADER.
    ShaderType GetType() const;
};

#endif // SHADER_H
