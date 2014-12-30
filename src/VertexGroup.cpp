#include "include/VertexGroup.h"

VertexGroup::VertexGroup()
{
    data = 0;
    vertexFormat = VertexFormat();
    vertexCount = 0;
}

void VertexGroup::Init(const VertexGroup& vg)
{
    vertexCount = vg.vertexCount;
    vertexFormat = VertexFormat(vg.vertexFormat);
    data = malloc(vertexCount * vertexFormat.GetStride());
}

void VertexGroup::Init(int vertexCount)
{
    this->vertexCount = vertexCount;

    //Create default vertexFormat
    vertexFormat = VertexFormat();
    VertexAttribute posAttr("pos", 3, GL_FLOAT), uvAttr("uv", 2, GL_FLOAT);
    vertexFormat.AddAttribute(posAttr);
    vertexFormat.AddAttribute(uvAttr);
    vertexFormat.SetPositionAttributeName("pos");
    vertexFormat.SetTexCoordsAttributeName("uv");

    int bytesAllocation = vertexCount * vertexFormat.GetStride();
    if(bytesAllocation == 0) data = 0;
    else data = malloc(bytesAllocation);
}

void VertexGroup::Init(const VertexFormat &vf)
{
    data = 0;
    vertexCount = 0;
    vertexFormat = VertexFormat(vf);
}

void VertexGroup::Init(int vertexCount, const VertexFormat &vf)
{
    this->vertexCount = vertexCount;
    vertexFormat = VertexFormat(vf);
    int bytesAllocation = vertexCount * vertexFormat.GetStride();
    if(bytesAllocation == 0) data = 0;
    else data = malloc(bytesAllocation);
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
    int offset = vertexFormat.GetOffsetOf(attributeName);
    if(offset == -1) return;
    offset += vertexFormat.GetStride() * vertexIndex;

    void *pdata  = (void*)((char*)data + offset);
    int type = vertexFormat.GetAttribute(attributeName).GetComponentsType();
    int numComponents = vertexFormat.GetAttribute(attributeName).GetComponentsNum();
    for(int i = 0; i < numComponents; ++i)
    {
        if(type == GL_DOUBLE)      *((double*)pdata + i) = *((double*)pvalue + i);
        else if(type == GL_FLOAT)  *((float*)pdata + i)  = *((float*)pvalue + i);
        else if(type == GL_INT)    *((int*)pdata + i)    = *((int*)pvalue + i);
        else if(type == GL_SHORT)  *((short*)pdata + i)  = *((short*)pvalue + i);
        else if(type == GL_BYTE)   *((char*)pdata + i)   = *((char*)pvalue + i);
    }
}

void* VertexGroup::GetAttributePointer(string attributeName, int vertexIndex) const
{
    if(data == 0) return (void*)0;
    return (void*)0;
}

int VertexGroup::GetVertexCount() { return vertexCount; }
void* VertexGroup::GetRawData() { return data; }
VertexFormat* VertexGroup::GetVertexFormatPointer() { return &vertexFormat; }
