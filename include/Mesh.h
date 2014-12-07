#ifndef MESH_H
#define MESH_H

#define GL_GLEXT_PROTOTYPES //Needed to include glext.h, to use glbuffers

#include <GL/gl.h>
#include <GL/glext.h>
#include <vector>
#include "Debug.h"
#include "Shader.h"
#include "Material.h"
#include "Component.h"
#include "Vector3.h"
#include "Vector2.h"

using namespace std;

class Mesh : public Component
{
private:

    unsigned int vertexBufferId;
    int vertexCount;

public:

    Material *material;
    Mesh();

    void Init(){}

    void Draw();
    void LoadFromFile(const char *filepath);

    int GetVertexCount();
};

#endif // MESH_H
