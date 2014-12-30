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
    Shader vertexShader(CZ_VERTEX_SHADER, "Shaders/vertexShader.glsl"),
           fragmentShader(CZ_FRAGMENT_SHADER, "Shaders/fragmentShader.glsl");
    material->AttachShader(vertexShader);
    material->AttachShader(fragmentShader);
    material->SetTexture(new Texture("models/textures/gordaco.bmp"));
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
    VertexGroup vg;
    DBG_ASSERT_RET(FileReader::ReadMeshFile(filepath, vg, vertexFormat, triangles));
    vertexCount = vg.GetVertexCount();
    if(vertexCount == 0) return false;

    int stride = vertexFormat.GetStride();
    //for(int i = 0; i < vertexCount * stride; ++i) if(i%4 == 0) DbgLog( i << ": " << *((float*)((char*)vg.GetRawData() + i)) );
    glBindBuffer(GL_ARRAY_BUFFER, vboId);
    glBufferData(GL_ARRAY_BUFFER, vertexCount * stride, vg.GetRawData(), GL_STATIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    vaoId = vertexFormat.CreateVAO(vboId); //CREATE THE VAO AND BIND THE VAO WITH THE VBO
    return true;
}

int Mesh::GetVertexCount()
{
    return vertexCount;
}


