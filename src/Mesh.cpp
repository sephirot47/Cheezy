#include "include/Mesh.h"

Mesh::Mesh()
{
    vertexCount = 0;
    triangles = true;
    type = "Mesh";
    vaoId = -1;

    glGenBuffers(1, &vboId);

    vertexFormat = new VertexFormat();
    VertexFormat::GetDefault(*vertexFormat);

    material = new Material();
    Material::GetDefault(*material);
}

Mesh::Mesh(const Mesh &mesh)
{
    vertexCount = mesh.vertexCount;
    triangles = mesh.triangles;
    type = "Mesh";
    vaoId = -1;

    glGenBuffers(1, &vboId);
    vertexFormat = new VertexFormat(*mesh.vertexFormat);
    material = new Material(*mesh.material);
}

Mesh::Mesh(VertexFormat &vf)
{
    vertexCount = 0;
    triangles = true;
    type = "Mesh";
    vaoId = -1;

    glGenBuffers(1, &vboId);

    vertexFormat = new VertexFormat(vf);

    material = new Material();
    Shader  *vertexShader   = new Shader(VertexShader, "Shaders/vertexShader.glsl"),
            *fragmentShader = new Shader(FragmentShader, "Shaders/fragmentShader.glsl");
    material->AttachShader(*vertexShader);
    material->AttachShader(*fragmentShader);
    material->SetTexture(new Texture("models/textures/gordaco.bmp"));
}

Mesh::~Mesh()
{
    if(vertexFormat){ vertexFormat->DeleteVAO(); delete vertexFormat;}
    if(material) delete material;
}

void Mesh::AddVertices(const vector<Vertex> &vertices, int startingIndex)
{
    /*
    glBindBuffer(GL_ARRAY_BUFFER, vboId);
    int vSize = vertexFormat->GetStride();
    glBufferSubData(GL_ARRAY_BUFFER, startingIndex * vSize, vertices.size() * vSize, &vertices[0]);
    glBindBuffer(GL_ARRAY_BUFFER, 0);*/
}

void Mesh::GetVertices(vector<Vertex> &vertices)
{

}

void Mesh::RemoveVertex(int i)
{

}

void Mesh::GetDefault(Mesh &m)
{
    m = Mesh();
}

void Mesh::Draw() const
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
    DBG_ASSERT_RET(FileReader::ReadMeshFile(filepath, vg, *vertexFormat, triangles));
    vertexCount = vg.GetVertexCount();
    if(vertexCount == 0) return false;

    int stride = vertexFormat->GetStride();
    glBindBuffer(GL_ARRAY_BUFFER, vboId);
    glBufferData(GL_ARRAY_BUFFER, vertexCount * stride, vg.GetRawData(), GL_STATIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    vaoId = vertexFormat->CreateVAOForMaterial(vboId, *material); //CREATE THE VAO AND BIND THE VAO WITH THE VBO
    return true;
}

int Mesh::GetVertexCount() const { return vertexCount; }

Material *Mesh::GetMaterial()
{
    return material;
}

VertexFormat *Mesh::GetVertexFormat()
{
    return vertexFormat;
}

void Mesh::Destroy()
{
}


