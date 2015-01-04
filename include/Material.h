#ifndef MATERIAL_H
#define MATERIAL_H

#define GL_GLEXT_PROTOTYPES //Needed to include glext.h, to use glbuffers

#include <GL/gl.h>
#include <GL/glext.h>
#include <map>
#include <vector>
#include "include/Debug.h"
#include "include/Shader.h"
#include "include/Component.h"
#include "include/Bindable.h"
#include "include/Texture.h"

#define CZ_MAX_MATERIAL_ERROR_LOG_SIZE 2056

using namespace std;

class Material : public Bindable
{
private:

    Shader *vertexShader, *fragmentShader;
    Texture *texture;
    map<string, vec4>  uniformsVec4;
    map<string, vec3>  uniformsVec3;
    map<string, vec2>  uniformsVec2;
    map<string, float> uniformsFloat;
    map<string, int>   uniformsInt;
    unsigned int programId;

public:

    Material();
    Material(const Material &m);
    virtual ~Material();

    static Material* GetDefault();

    ///\brief Attaches to the Material a Shader of type shaderType
    ///       If there was a previous attached Shader of the same type, it will be replaced
    ///       If something goes wrong, returns false. Otherwise returns true.
    bool AttachShader(Shader &shader);

    ///\brief Returns the id of the shader attached to this Material
    ///       If no shader is attached, returns -1
    int GetShaderId(unsigned int shaderType) const;
    int GetProgramId() const;

    void SetTexture(Texture *t);

    void SetUniform(string name, vec4 value);
    void SetUniform(string name, vec3 value);
    void SetUniform(string name, vec2 value);
    void SetUniform(string name, float value);
    void SetUniform(string name, int value);

    int GetAttributeLocation(string attributeName) const;

    void Bind();
    void UnBind();
};

#endif // MATERIAL_H
