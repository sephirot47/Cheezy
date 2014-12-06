#ifndef MATERIAL_H
#define MATERIAL_H

#define GL_GLEXT_PROTOTYPES //Needed to include glext.h, to use glbuffers

#include <GL/gl.h>
#include <GL/glext.h>
#include <vector>
#include "Debug.h"
#include "Component.h"
#include "Vector3.h"
#include "Vector2.h"

using namespace std;

class Material
{
private:

    Shader *shader;

public:

    Material();

    void SetShader(Shader &shader);

    ///\brief Returns the id of the shader attached to this Material
    ///       If no shader is attached, returns -1
    int GetShaderId();
};

#endif // MATERIAL_H
