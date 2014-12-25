#include "include/VertexFormat.h"

VertexFormat VertexFormat::Default = VertexFormat();

VertexFormat::VertexFormat()
{
    posName = uvsName = normalsName = "";
    vaoId = -1;
}

int VertexFormat::GetOffsetOf(string attributeName) const
{
    int off = 0;
    for(auto it : attributes)
    {
        if(it.second->GetName() != attributeName) off += it.second->GetSize();
        else return off;
    }
    return -1;
}

int VertexFormat::GetSizeOf(string attributeName) const
{
    if(attributes.find(attributeName) != attributes.end())
        return attributes.find(attributeName)->second->GetSize();
    return -1;
}

int VertexFormat::GetStride() const
{
    int size = 0;
    for(auto it : attributes) size += it.second->GetSize();
    return size;
}

void VertexFormat::AddAttribute(VertexAttribute &va)
{
    DBG_ASSERT_RET_VOID_MSG((va.GetName() == ""), "The vertex attribute you passed doesn't have a name.");
    DBG_ASSERT_RET_VOID_MSG((va.GetComponentsNum() == 0), "The vertex attribute have 0 elements.");
    DBG_ASSERT_RET_VOID_MSG((va.GetSize() == 0), "The vertex attribute have elements of size 0.");

    attributes[va.GetName()] = new VertexAttribute(va.GetName(), va.GetComponentsNum(), va.GetComponentsType());
}
void VertexFormat::AddAttribute(VertexAttribute *va) {AddAttribute(*va);}

bool VertexFormat::HasAttributeOfType(int type) const
{
    for(auto it : attributes)
    {
        if(it.second->GetComponentsType() == type) return true;
    }
    return false;
}

VertexAttribute VertexFormat::GetAttribute(string name)
{
    return *attributes[name];
}

void VertexFormat::DeleteAttribute(VertexAttribute &va)
{
    if(attributes.find(va.GetName()) == attributes.end())
        DbgWarning("Trying to erase an attribute that doesn't exist.");
    else attributes.erase(va.GetName());
}
void VertexFormat::DeleteAttribute(VertexAttribute *va) {DeleteAttribute(*va);}

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

unsigned int VertexFormat::CreateVAO()
{
    glGenVertexArrays(1, &vaoId);
    if(vaoId < 0) { DbgError("Error creating the VAO"); return -1; }
    glBindVertexArray(vaoId);

    int i = 0;
    int offset = 0;
    int stride = GetStride();
    for(auto it : attributes)
    {
        glEnableVertexAttribArray(i++);
        glVertexAttribPointer(vaoId,
                              it.second->GetComponentsNum(),
                              it.second->GetComponentsType(),
                              GL_FALSE,
                              stride,
                              (void*)offset
                              );
        offset += it.second->GetSize();
    }
    glBindVertexArray(0);
    return vaoId;
}

void VertexFormat::DeleteVAO()
{
    if(vaoId < 0) return;
    glDeleteVertexArrays(1, &vaoId);
}



