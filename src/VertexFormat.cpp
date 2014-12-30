#include "include/VertexFormat.h"

VertexFormat::VertexFormat()
{
    posName = uvsName = normalsName = "";
    attributesNum = 0;
    vaoId = -1;
}

VertexFormat::VertexFormat(const VertexFormat &vf) : VertexFormat()
{
    for(int i = 0; i < vf.attributesNum; ++i)
    {
        VertexAttribute attr = vf.attributes.find(vf.insertionOrder[i])->second;
        this->AddAttribute(attr);
    }

    this->posName = vf.posName;
    this->uvsName = vf.uvsName;
    this->normalsName = vf.normalsName;
}

VertexFormat::~VertexFormat()
{
}

int VertexFormat::GetOffsetOf(string attributeName) const
{
    int off = 0;
    for(int i = 0; i < attributesNum; ++i)
    {
        if(attributes.find(insertionOrder[i])->second.GetName() != attributeName)
            off += attributes.find(insertionOrder[i])->second.GetSize();
        else
            return off;
    }
    return -1;
}

int VertexFormat::GetOffsetOf(int index) const
{
    if(index >= attributesNum or index < 0) { DbgWarning("Trying to get the offset of an attribute of an index out of bounds (returning -1)"); return -1; }
    int off = 0;
    for(int i = 0; i < attributesNum; ++i)
    {
        if(i != index)
            off += attributes.find(insertionOrder[i])->second.GetSize();
        else
            return off;
    }
    return -1;
}

int VertexFormat::GetSizeOf(string attributeName) const
{
    if(attributes.find(attributeName) != attributes.end())
        return attributes.find(attributeName)->second.GetSize();
    return -1;
}

int VertexFormat::GetSizeOf(int i) const
{
    if(i >= attributesNum or i < 0) { DbgWarning("Trying to get the size of an attribute of an index out of bounds (returning -1)"); return -1; }
    else return attributes.find(insertionOrder[i])->second.GetSize();
}

int VertexFormat::GetStride() const
{
    int size = 0;
    for(int i = 0; i < attributesNum; ++i)
        size += attributes.find(insertionOrder[i])->second.GetSize();
    return size;
}

VertexAttribute VertexFormat::GetAttribute(int i) const
{
    if(i >= attributesNum or i < 0) { DbgWarning("Trying to get an attribute of an index out of bounds (returning empty VertexAttribute"); return VertexAttribute(); }
    else return attributes.find(insertionOrder[i])->second;
}

int VertexFormat::GetAttributesNum() const
{
    return attributesNum;
}

void VertexFormat::AddAttribute(VertexAttribute &va)
{
    DBG_ASSERT_RET_VOID_MSG((va.GetName() == ""), "The vertex attribute you passed doesn't have a name.");
    DBG_ASSERT_RET_VOID_MSG((va.GetComponentsNum() == 0), "The vertex attribute have 0 elements.");
    DBG_ASSERT_RET_VOID_MSG((va.GetSize() == 0), "The vertex attribute have elements of size 0.");

    ++attributesNum;
    attributes[va.GetName()] = VertexAttribute(va.GetName(), va.GetComponentsNum(), va.GetComponentsType());
    insertionOrder.push_back(va.GetName());
}

VertexAttribute VertexFormat::GetAttribute(string name) const
{
    return attributes.find(name)->second;
}

void VertexFormat::SetPositionAttributeName(string attributeName)
{
    if(attributes.find(attributeName) != attributes.end()) posName = attributeName;
    else DbgWarning("Setting position attribute as an attribute that doesn't exist (" << attributeName << ")");
}

void VertexFormat::SetTexCoordsAttributeName(string attributeName)
{
    if(attributes.find(attributeName) != attributes.end()) uvsName = attributeName;
    else DbgWarning("Setting texCoord attribute as an attribute that doesn't exist (" << attributeName << ")");
}

void VertexFormat::SetNormalsAttributeName(string attributeName)
{
    if(attributes.find(attributeName) != attributes.end()) normalsName = attributeName;
    else DbgWarning("Setting normals attribute as an attribute that doesn't exist (" << attributeName << ")");
}

VertexAttribute VertexFormat::GetPositionAttribute()
{
    if(posName != "") return attributes[posName];
    return VertexAttribute();
}

VertexAttribute VertexFormat::GetTexCoordsAttribute()
{
    if(uvsName != "") return attributes[uvsName];
    return VertexAttribute();
}

VertexAttribute VertexFormat::GetNormalsAttribute()
{
    if(normalsName != "") return attributes[normalsName];
    return VertexAttribute();
}

unsigned int VertexFormat::CreateVAO(int vboId)
{
    glGenVertexArrays(1, &vaoId);
    if(vaoId < 0) { DbgError("Error generating the VAO"); return -1; }

    glBindVertexArray(vaoId);
    glBindBuffer(GL_ARRAY_BUFFER, vboId);
    int offset = 0, stride = GetStride();
    for(int i = 0; i < attributesNum; ++i)
    {
        VertexAttribute attr = attributes.find(insertionOrder[i])->second;
        glVertexAttribPointer(i,
                              attr.GetComponentsNum(),
                              attr.GetComponentsType(),
                              GL_FALSE,
                              stride,
                              (void*)offset);
        glEnableVertexAttribArray(i);
        offset += attr.GetSize();
    }
    glBindVertexArray(0);
    return vaoId;
}

void VertexFormat::DeleteVAO()
{
    if(vaoId < 0) return;
    glDeleteVertexArrays(1, &vaoId);
}



