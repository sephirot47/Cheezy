#include "include/Mesh.h"

Mesh::Mesh(VertexFormat vf)
{
    vertexCount = 0;
    triangles = true;

    type = "Mesh";
    glGenBuffers(1, &vboId);

    vertexFormat = vf;
    vaoId = vf.CreateVAO();

    material = new Material();
    material->AttachShader(new Shader(CZ_VERTEX_SHADER, "Shaders/vertexShader.glsl"));
    material->AttachShader(new Shader(CZ_FRAGMENT_SHADER, "Shaders/fragmentShader.glsl"));
    material->SetTexture(new Texture("models/textures/luigiD.jpg"));
}

Mesh::~Mesh()
{
    vertexFormat.DeleteVAO();
    delete material;
}

void Mesh::Draw()
{
    if(vertexCount <= 0) return;

    glBindVertexArray(vaoId);
    glBindBuffer(GL_ARRAY_BUFFER, vboId);
    //DBG_ASSERT_GL( glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void *)(0)) );               //vertices pos (index 0)
    //DBG_ASSERT_GL( glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void *)(sizeof(vec3))) ); //vertices uv  (index 1)

    if(material) material->Bind(); //Use the material
    DBG_ASSERT_GL(glDrawArrays(triangles ? GL_TRIANGLES : GL_QUADS, 0, vertexCount));
    if(material) material->UnBind();

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}

bool Mesh::LoadFromFile(const char *filepath)
{
    vector<Vertex> vertices;
    DBG_ASSERT_RET(FileReader::ReadMeshFile(filepath, vertices, vertexFormat, triangles));
    vertexCount = vertices.size();
    cout << "Finished loading from file" << endl;

    glBindBuffer(GL_ARRAY_BUFFER, vboId);
    glBufferData(GL_ARRAY_BUFFER, vertexCount * sizeof(Vertex), &vertices[0], GL_STATIC_DRAW); //Load the mesh to the GPU
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    return true;
}

int Mesh::GetVertexCount()
{
    return vertexCount;
}

