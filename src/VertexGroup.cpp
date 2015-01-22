#include "include/VertexGroup.h"

VertexGroup::VertexGroup()
{
    data = 0;
    vertexFormat = new VertexFormat();
    vertexCount = 0;
}

VertexGroup::VertexGroup(const VertexGroup &vg)
{
    if(data) free(data);
    if(vg.data)
    {
        int dataSize = vg.vertexCount * vg.vertexFormat->GetStride();
        data = malloc(dataSize);
        memcpy(data, vg.data, dataSize);
    }
    else data = 0;

    vertexFormat = new VertexFormat(*vg.vertexFormat);
    vertexCount = vg.vertexCount;
}

VertexGroup &VertexGroup::operator=(const VertexGroup &vg)
{
    if(this == &vg) return *this;

    if(data) free(data);
    if(vg.data)
    {
        int dataSize = vg.vertexCount * vg.vertexFormat->GetStride();
        data = malloc(dataSize);
        memcpy(data, vg.data, dataSize);
    }
    else data = 0;

    vertexFormat = new VertexFormat(*vg.vertexFormat);
    vertexCount = vg.vertexCount;
    return *this;
}

void VertexGroup::Init(const VertexGroup& vg)
{
    vertexCount = vg.vertexCount;
    vertexFormat = new VertexFormat(*vg.vertexFormat);
    data = malloc(vertexCount * vertexFormat->GetStride());
}

void VertexGroup::Init(int vertexCount)
{
    this->vertexCount = vertexCount;

    VertexFormat::GetDefault(*vertexFormat); //Create default vertexFormat

    int bytesAllocation = vertexCount * vertexFormat->GetStride();
    if(bytesAllocation == 0) data = 0;
    else data = malloc(bytesAllocation);
}

void VertexGroup::Init(const VertexFormat &vf)
{
    data = 0;
    vertexCount = 0;
    vertexFormat = new VertexFormat(vf);
}

void VertexGroup::Init(int vertexCount, const VertexFormat &vf)
{
    this->vertexCount = vertexCount;
    vertexFormat = new VertexFormat(vf);
    int bytesAllocation = vertexCount * vertexFormat->GetStride();
    if(bytesAllocation == 0) data = 0;
    else data = malloc(bytesAllocation);
}

void VertexGroup::Init(const vector<Vertex> &vertices)
{
    if(data != 0) free(data);
    data = malloc(vertices.size() * vertexFormat->GetStride());
    for(unsigned int i = 0; i < vertices.size(); ++i)
    {
        SetVertex(i, vertices[i]);
    }
}

VertexGroup::~VertexGroup()
{
    if(data)
    {
        free(data);
        data = 0;
    }
}

void VertexGroup::SetAttribute(string attributeName, void *pvalue, int vertexIndex)
{
    if(data == 0) return;
    int offset = vertexFormat->GetOffsetOf(attributeName);
    if(offset == -1) return;
    offset += vertexFormat->GetStride() * vertexIndex;

    void *pdata  = (void*)((char*)data + offset);
    int type = vertexFormat->GetAttribute(attributeName).GetComponentsType();
    int numComponents = vertexFormat->GetAttribute(attributeName).GetComponentsCount();
    for(int i = 0; i < numComponents; ++i)
    {
        if(type == GL_DOUBLE)      *((double*)pdata + i) = *((double*)pvalue + i);
        else if(type == GL_FLOAT)  *((float*)pdata + i)  = *((float*)pvalue + i);
        else if(type == GL_INT)    *((int*)pdata + i)    = *((int*)pvalue + i);
        else if(type == GL_SHORT)  *((short*)pdata + i)  = *((short*)pvalue + i);
        else if(type == GL_BYTE)   *((char*)pdata + i)   = *((char*)pvalue + i);
    }
}

Vertex* VertexGroup::GetVertexPointer(int vertexIndex) const
{
    if(vertexIndex < 0 or vertexIndex > vertexCount)
    {
        DbgWarning("Trying to get a pointer to a vertex out of bounds(returning null pointer)");
        return 0;
    }
    return (Vertex*)((char*)data + vertexIndex * vertexFormat->GetStride());
}

void* VertexGroup::GetAttributePointer(string attributeName, int vertexIndex) const
{
    if(vertexIndex < 0 or vertexIndex >= vertexCount)
    {
        DbgWarning("Trying to get a pointer to an attribute of a vertex out of bounds (returning null pointer)");
        return (void*)0;
    }
    int offset = vertexFormat->GetOffsetOf(attributeName);
    if(offset == - 1)
    {
        DbgWarning("Trying to get a pointer to an attribute that doesn't exist (returning null pointer)");
        return (void*)0;
    }

    Vertex *v = GetVertexPointer(vertexIndex);
    return (void*)((char*)v + offset);
}

int VertexGroup::GetVertexCount() const { return vertexCount; }
void* VertexGroup::GetRawData() const { return data; }
VertexFormat VertexGroup::GetVertexFormat() const { return *vertexFormat; }


void VertexGroup::SetVertex(int vertexIndex, const Vertex &v)
{
    if(vertexIndex < 0 or vertexIndex > vertexCount)
    {
        DbgWarning("Trying to set a vertex out of bounds (doing nothing)");
        return;
    }
    Vertex *vdata = GetVertexPointer(vertexIndex);
    memcpy(vdata, &v, vertexFormat->GetStride());
}

Vertex VertexGroup::GetVertex(int vertexIndex) const
{
    if(vertexIndex < 0 or vertexIndex > vertexCount)
    {
        DbgWarning("Trying to get a vertex out of bounds (returning empty Vertex)");
        return Vertex();
    }
    return *((Vertex*)((char*)data + vertexIndex * vertexFormat->GetStride()));
}

