#include "include/VertexFormat.h"

VertexFormat::VertexFormat()
{
    posName = uvsName = normalsName = "";
    vaoId = -1;
}

VertexFormat::VertexFormat(VertexFormat &vf) : VertexFormat()
{
    for(auto it : vf.attributes)
    {
        VertexAttribute attr(it.second.GetName(), it.second.GetComponentsNum(), it.second.GetComponentsType());
        this->AddAttribute(attr);
    }
}

VertexFormat::~VertexFormat()
{
}

int VertexFormat::GetOffsetOf(string attributeName) const
{
    int off = 0;
    for(auto it : attributes)
    {
        if(it.second.GetName() != attributeName) off += it.second.GetSize();
        else return off;
    }
    return -1;
}

int VertexFormat::GetSizeOf(string attributeName) const
{
    if(attributes.find(attributeName) != attributes.end())
        return attributes.find(attributeName)->second.GetSize();
    return -1;
}

int VertexFormat::GetStride() const
{
    int size = 0;
    for(auto it : attributes) size += it.second.GetSize();
    return size;
}

void VertexFormat::AddAttribute(VertexAttribute &va)
{
    DBG_ASSERT_RET_VOID_MSG((va.GetName() == ""), "The vertex attribute you passed doesn't have a name.");
    DBG_ASSERT_RET_VOID_MSG((va.GetComponentsNum() == 0), "The vertex attribute have 0 elements.");
    DBG_ASSERT_RET_VOID_MSG((va.GetSize() == 0), "The vertex attribute have elements of size 0.");

    attributes[va.GetName()] = VertexAttribute(va.GetName(), va.GetComponentsNum(), va.GetComponentsType());
}

VertexAttribute VertexFormat::GetAttribute(string name)
{
    return attributes[name];
}

void VertexFormat::SetPositionAttribute(string attributeName)
{
    if(attributes.find(attributeName) != attributes.end()) posName = attributeName;
    else DbgWarning("Setting position attribute as an attribute that doesn't exist (" << attributeName << ")");
}

void VertexFormat::SetTexCoordsAttribute(string attributeName)
{
    if(attributes.find(attributeName) != attributes.end()) uvsName = attributeName;
    else DbgWarning("Setting texCoord attribute as an attribute that doesn't exist (" << attributeName << ")");
}

void VertexFormat::SetNormalsAttribute(string attributeName)
{
    if(attributes.find(attributeName) != attributes.end()) normalsName = attributeName;
    else DbgWarning("Setting normals attribute as an attribute that doesn't exist (" << attributeName << ")");
}

unsigned int VertexFormat::CreateVAO(int vboId)
{
    glGenVertexArrays(1, &vaoId);
    if(vaoId < 0) { DbgError("Error creating the VAO"); return -1; }

    glBindVertexArray(vaoId);
    glBindBuffer(GL_ARRAY_BUFFER, vboId);

    int i = 0, offset = 0, stride = GetStride();
    DbgLog("----------------------");
    DbgLog("Creating VAO: stride: " << GetStride() << ", offset: " << offset);
    for(auto it : attributes)
    {
        DbgLog("glVertexAttribPointer(" << i << ", " << it.second.GetComponentsNum() << ", " << it.second.GetComponentsType() << ", false, " << stride << ")");
        glVertexAttribPointer(i,
                              it.second.GetComponentsNum(),
                              it.second.GetComponentsType(),
                              GL_FALSE,
                              stride,
                              (void*)offset);
        DbgLog("Enable va: " << i);
        glEnableVertexAttribArray(i);

        offset += it.second.GetSize();
        ++i;
    }
    DbgLog("----------------------");
    glBindVertexArray(0);
    return vaoId;
}

void VertexFormat::DeleteVAO()
{
    if(vaoId < 0) return;
    glDeleteVertexArrays(1, &vaoId);
}



