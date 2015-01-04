#ifndef MESH_H
#define MESH_H

#define GL_GLEXT_PROTOTYPES //Needed to include glext.h, to use glbuffers

#include <GL/gl.h>
#include <GL/glext.h>
#include <string.h>
#include <vector>
#include <fstream>
#include <sstream>

#include "include/Debug.h"
#include "include/Shader.h"
#include "include/Vertex.h"
#include "include/VertexFormat.h"
#include "include/Material.h"
#include "include/Component.h"
#include "include/FileReader.h"

using namespace std;

class Mesh : public Component
{
private:

    unsigned int vboId, vaoId;
    int vertexCount;
    bool triangles;

public:

    static Mesh* GetDefault();

    Material *material;
    VertexFormat *vertexFormat;

    Mesh();
    Mesh(const Mesh& mesh);
    Mesh(VertexFormat& vf);
    virtual ~Mesh();

    void Init() {}

    void Draw() const;
    bool LoadFromFile(const char *filepath);

    int GetVertexCount() const;
};

#endif // MESH_H
