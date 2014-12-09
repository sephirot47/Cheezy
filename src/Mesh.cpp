#include "Mesh.h"

Mesh::Mesh()
{
    vertexCount = 0;
    type = "Mesh";
    glGenBuffers(1, &vertexBufferId);

    material = new Material();

    Shader *vertexShader = new Shader(CZ_VERTEX_SHADER, "Shaders/vertexShader.glsl");
    Shader *fragmentShader = new Shader(CZ_FRAGMENT_SHADER, "Shaders/fragmentShader.glsl");

    material->AttachShader(*vertexShader);
    material->AttachShader(*fragmentShader);
}

void Mesh::Draw()
{
    if(vertexCount <= 0) return;

    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, vertexBufferId);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void *)(0));               //vertices pos (index 0)
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void *)(sizeof(Vector3))); //vertices uv  (index 1)

    DBG_ASSERT_GL(material->UseProgram()); //Use the shader
    DBG_ASSERT_GL(glDrawArrays(GL_TRIANGLES, 0, vertexCount));
    DBG_ASSERT_GL(material->UnUseProgram()); //Dont use this shaders from now on

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glDisableVertexAttribArray(0);
}

bool Mesh::LoadFromFile(const char *filepath)
{
    vector<Vertex> vertices;
    DBG_ASSERT_RET(FileReader::ReadOBJ(filepath, vertices));
    vertexCount = vertices.size();

    glBindBuffer(GL_ARRAY_BUFFER, vertexBufferId);
    glBufferData(GL_ARRAY_BUFFER, vertexCount * sizeof(Vertex), &vertices[0], GL_STATIC_DRAW); //Load the mesh to the GPU
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    return true;
}

int Mesh::GetVertexCount()
{
    return vertexCount;
}

