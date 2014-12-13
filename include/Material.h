#ifndef MATERIAL_H
#define MATERIAL_H

#define GL_GLEXT_PROTOTYPES //Needed to include glext.h, to use glbuffers

#include <GL/gl.h>
#include <GL/glext.h>
#include <vector>
#include "Debug.h"
#include "Shader.h"
#include "Component.h"
#include "Bindable.h"
#include "Texture.h"
#include "Vector3.h"
#include "Vector2.h"

#define CZ_MAX_MATERIAL_ERROR_LOG_SIZE 2056

using namespace std;

class Material : public Bindable
{
private:

    Shader *vertexShader, *fragmentShader;
    Texture *texture;
    unsigned int programId;

public:

    Material();

    ///\brief Attaches to the Material a Shader of type shaderType
    ///       If there was a previous attached Shader of the same type, it will be replaced
    ///       If something goes wrong, returns false. Otherwise returns true.
    bool AttachShader(Shader &shader);
    bool AttachShader(Shader *shader);

    ///\brief Returns the id of the shader attached to this Material
    ///       If no shader is attached, returns -1
    int GetShaderId(unsigned int shaderType);

    void SetTexture(Texture &t);
    void SetTexture(Texture *t);

    void Bind();
    void UnBind();
};

#endif // MATERIAL_H
