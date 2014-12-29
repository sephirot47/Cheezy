#include "include/Mesh.h"

Mesh::Mesh(VertexFormat &vf)
{
    vertexCount = 0;
    triangles = true;
    type = "Mesh";
    vaoId = -1;

    glGenBuffers(1, &vboId);

    vertexFormat = VertexFormat(vf);

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
    if(vertexCount <= 0 or vaoId < 0) return;

    glEnableClientState(GL_VERTEX_ARRAY);
    glBindVertexArray(vaoId);

    if(material) material->Bind(); //Use the material
    DBG_ASSERT_GL(glDrawArrays(triangles ? GL_TRIANGLES : GL_QUADS, 0, vertexCount));
    if(material) material->UnBind();

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
    glDisableClientState(GL_VERTEX_ARRAY);
}

bool Mesh::LoadFromFile(const char *filepath)
{
    void *rawVerticesData = 0;
    DBG_ASSERT_RET(FileReader::ReadMeshFile(filepath, rawVerticesData, vertexCount, vertexFormat, triangles));
    if(rawVerticesData == 0) return false;

    int stride = vertexFormat.GetStride();
    glBindBuffer(GL_ARRAY_BUFFER, vboId);
    glBufferData(GL_ARRAY_BUFFER, vertexCount * stride, rawVerticesData, GL_STATIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    vaoId = vertexFormat.CreateVAO(vboId); //CREATE THE VAO AND BIND THE VAO WITH THE VBO

    free(rawVerticesData);
    return true;
}

int Mesh::GetVertexCount()
{
    return vertexCount;
}


