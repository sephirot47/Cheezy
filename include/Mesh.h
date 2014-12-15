#ifndef MESH_H
#define MESH_H

#define GL_GLEXT_PROTOTYPES //Needed to include glext.h, to use glbuffers

#include <GL/gl.h>
#include <GL/glext.h>
#include <string.h>
#include <vector>
#include <fstream>
#include <sstream>
#include "Debug.h"
#include "Shader.h"
#include "Vertex.h"
#include "Material.h"
#include "Component.h"
#include "FileReader.h"
#include "Vector3.h"
#include "Vector2.h"

using namespace std;

class Mesh : public Component
{
private:

    unsigned int vertexBufferId;
    int vertexCount;
    bool triangles;

public:

    Material *material;
    Mesh();
    virtual ~Mesh();

    void Init(){}

    void Draw();
    bool LoadFromFile(const char *filepath);

    int GetVertexCount();
};

#endif // MESH_H
