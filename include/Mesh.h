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

    Material *material;
    VertexFormat *vertexFormat;

public:


    static void GetDefault(Mesh &m);

    Mesh();
    Mesh(const Mesh& mesh);
    Mesh(VertexFormat& vf);
    virtual ~Mesh();

    virtual ComponentType GetType() const { return type; }

    void AddVertices(const vector<Vertex> &vertices, int startingIndex);
    void GetVertices(vector<Vertex> &vertices);
    void RemoveVertex(int i);

    void Draw() const;
    bool LoadFromFile(const char *filepath);

    int GetVertexCount() const;

    Material* GetMaterial();
    VertexFormat* GetVertexFormat();

    void Destroy();
};

#endif // MESH_H
