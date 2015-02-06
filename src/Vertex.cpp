#include "include/Vertex.h"

Vertex::Vertex()
{
    data = nullptr;
}

Vertex::Vertex(const Vertex &v, const VertexFormat &vf)
{
    int stride = vf.GetStride();
    if(v.data and stride > 0)
    {
        data = malloc(stride);
        memcpy(data, v.data, stride);
    }
    else data = nullptr;
}

Vertex &Vertex::operator=(const Vertex &v)
{
    data = v.data; //Pfff...por poner algo :S
    return *this;
}

Vertex::~Vertex()
{
    if(data)
    {
        free(data);
        data = nullptr;
    }
}

void Vertex::Init(const VertexFormat &vf)
{
    int totalVertexSize = vf.GetStride();
    if(totalVertexSize > 0) data = malloc(totalVertexSize);
    else data = nullptr;
}

void* Vertex::GetAttributePointer(string name, const VertexFormat &vf) const
{
    int offset = vf.GetOffsetOf(name);
    if(offset == -1) return nullptr; //No existe el atributo, return
    return (void*)((char*)data + offset); //(fem cast a char xk la aritmetica de punters sumi de byte en byte(si es void no sap com sumar))
}

bool Vertex::HasAttribute(string name, const VertexFormat &vf) const
{
    int offset = vf.GetOffsetOf(name);
    return (offset != -1);
}

void Vertex::SetAttribute(string name, void* pvalue, const VertexFormat &vf)
{
    int offset = vf.GetOffsetOf(name);
    if(offset == -1) return;
    int type = vf.GetAttribute(name).GetComponentsType();
    void *pdata  = GetAttributePointer(name, vf);
    for(int i = 0; i < vf.GetAttribute(name).GetComponentsCount(); ++i)
    {
        if(type == GL_DOUBLE)      *((double*)pdata + i)        = *((double*)pvalue + i);
        else if(type == GL_FLOAT)  *((float*)pdata + i)         = *((float*)pvalue + i);
        else if(type == GL_INT)    *((int*)pdata + i)           = *((int*)pvalue + i);
        else if(type == GL_SHORT)  *((short*)pdata + i)         = *((short*)pvalue + i);
        else if(type == GL_BYTE)   *((unsigned char*)pdata + i) = *((unsigned char*)pvalue + i);
    }
}
