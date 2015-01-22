#include "include/VertexFormat.h"

VertexFormat::VertexFormat()
{
    posName = uvsName = normalsName = "";
    attributesCount = 0;
    vaoId = -1;
}

VertexFormat::VertexFormat(const VertexFormat &vf) : VertexFormat()
{
    for(int i = 0; i < vf.attributesCount; ++i)
    {
        auto it = vf.attributes.find(vf.insertionOrder[i]);
        if(it != vf.attributes.end())
        {
            this->AddAttribute(it->second);
        }
    }

    this->posName = vf.posName;
    this->uvsName = vf.uvsName;
    this->normalsName = vf.normalsName;
}

VertexFormat &VertexFormat::operator=(const VertexFormat &vf)
{
    if(this == &vf) return *this;
    posName = vf.posName;
    uvsName = vf.uvsName;
    normalsName = vf.normalsName;
    attributesCount = vf.attributesCount;
    attributes = vf.attributes;
    insertionOrder = vf.insertionOrder;
    vaoId = -1;
    return *this;
}

VertexFormat::~VertexFormat()
{
}

void VertexFormat::GetDefault(VertexFormat &vf)
{
    string defaultVertexFormatPositionName = "pos";
    string defaultVertexFormatTexCoordName = "uv";
    string defaultVertexFormatNormalsName  = "normal";

    VertexAttribute posAttr(defaultVertexFormatPositionName, 3, GL_FLOAT),
                     uvAttr(defaultVertexFormatTexCoordName, 2, GL_FLOAT),
                 normalAttr(defaultVertexFormatNormalsName,  3, GL_FLOAT);

    vf = VertexFormat();
    vf.AddAttribute(posAttr);
    vf.AddAttribute(uvAttr);
    vf.AddAttribute(normalAttr);
    vf.SetPositionAttributeName(defaultVertexFormatPositionName);
    vf.SetTexCoordsAttributeName(defaultVertexFormatTexCoordName);
    vf.SetNormalsAttributeName(defaultVertexFormatNormalsName);
}

int VertexFormat::GetOffsetOf(string attributeName) const
{
    int off = 0;
    for(int i = 0; i < attributesCount; ++i)
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
    if(index >= attributesCount or index < 0) { DbgWarning("Trying to get the offset of an attribute of an index out of bounds (returning -1)"); return -1; }
    int off = 0;
    for(int i = 0; i < attributesCount; ++i)
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
    if(i >= attributesCount or i < 0) { DbgWarning("Trying to get the size of an attribute of an index out of bounds (returning -1)"); return -1; }
    else return attributes.find(insertionOrder[i])->second.GetSize();
}

int VertexFormat::GetStride() const
{
    int size = 0;
    for(int i = 0; i < attributesCount; ++i)
        size += attributes.find(insertionOrder[i])->second.GetSize();
    return size;
}

VertexAttribute VertexFormat::GetAttribute(int i) const
{
    if(i >= attributesCount or i < 0) { DbgWarning("Trying to get an attribute of an index out of bounds (returning empty VertexAttribute"); return VertexAttribute(); }
    else return attributes.find(insertionOrder[i])->second;
}

int VertexFormat::GetAttributesNum() const
{
    return attributesCount;
}

void VertexFormat::AddAttribute(const VertexAttribute &va)
{
    DBG_ASSERT_RET_VOID_MSG((va.GetName() == ""), "The vertex attribute you passed doesn't have a name.");
    DBG_ASSERT_RET_VOID_MSG((va.GetComponentsCount() == 0), "The vertex attribute have 0 elements.");
    DBG_ASSERT_RET_VOID_MSG((va.GetSize() == 0), "The vertex attribute have elements of size 0.");

    ++attributesCount;
    attributes[va.GetName()] = VertexAttribute(va.GetName(), va.GetComponentsCount(), va.GetComponentsType());
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

VertexAttribute VertexFormat::GetPositionAttribute() const
{
    if(posName != "") return attributes.find(posName)->second;
    return VertexAttribute();
}

VertexAttribute VertexFormat::GetTexCoordsAttribute() const
{
    if(uvsName != "") return attributes.find(uvsName)->second;
    return VertexAttribute();
}

VertexAttribute VertexFormat::GetNormalsAttribute() const
{
    if(normalsName != "") return attributes.find(normalsName)->second;
    return VertexAttribute();
}

int VertexFormat::CreateVAO(int vboId)
{
    glGenVertexArrays(1, &vaoId);
    if(vaoId < 0) { DbgError("Error generating the VAO. Returning -1."); return -1; }

    glBindVertexArray(vaoId);
    glBindBuffer(GL_ARRAY_BUFFER, vboId);
    int offset = 0, stride = GetStride();
    for(int i = 0; i < attributesCount; ++i)
    {
        VertexAttribute attr = attributes.find(insertionOrder[i])->second;
        glVertexAttribPointer(i,
                              attr.GetComponentsCount(),
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

int VertexFormat::CreateVAOForMaterial(int vboId, const Material &material)
{
    int programId = material.GetProgramId();
    if(programId < 0) { DbgWarning("Passing a material whose program isn't linked yet. Returning -1."); return -1;}

    glGenVertexArrays(1, &vaoId);
    if(vaoId < 0) { DbgError("Error generating the VAO"); return -1; }

    glBindVertexArray(vaoId);
    glBindBuffer(GL_ARRAY_BUFFER, vboId);


    int offset = 0, stride = GetStride();
    for(int i = 0; i < attributesCount; ++i)
    {
        int location = glGetAttribLocation(programId, insertionOrder[i].c_str());
        if(location < 0) continue;

        VertexAttribute attr = attributes.find(insertionOrder[i])->second;
        glVertexAttribPointer(location,
                              attr.GetComponentsCount(),
                              attr.GetComponentsType(),
                              GL_FALSE,
                              stride,
                              (void*)offset);
        glEnableVertexAttribArray(location);
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



