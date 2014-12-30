#include "include/Vertex.h"

Vertex::Vertex()
{
    data = 0;
}

Vertex::~Vertex()
{
    if(data)
    {
        free(data);
        data = 0;
    }
}

void Vertex::Create(const VertexFormat &vf)
{
    int totalVertexSize = vf.GetStride();
    if(totalVertexSize > 0) data = malloc(totalVertexSize);
    else data = 0;
}

void* Vertex::GetAttributePointer(string name, VertexFormat &vf)
{
    int offset = vf.GetOffsetOf(name);
    if(offset == -1) return 0; //No existe el atributo, return
    return (void*)((char*)data + offset); //(fem cast a char xk la aritmetica de punters sumi de byte en byte(si es void no sap com sumar))
}

bool Vertex::HasAttribute(string name, VertexFormat &vf)
{
    int offset = vf.GetOffsetOf(name);
    return (offset != -1);
}

void Vertex::SetAttribute(string name, void* pvalue, VertexFormat &vf)
{
    int offset = vf.GetOffsetOf(name);
    if(offset == -1) return;
    int type = vf.GetAttribute(name).GetComponentsType();
    void *pdata  = GetAttributePointer(name, vf);
    for(int i = 0; i < vf.GetAttribute(name).GetComponentsNum(); ++i)
    {
        if(type == GL_DOUBLE)      *((double*)pdata + i)        = *((double*)pvalue + i);
        else if(type == GL_FLOAT)  *((float*)pdata + i)         = *((float*)pvalue + i);
        else if(type == GL_INT)    *((int*)pdata + i)           = *((int*)pvalue + i);
        else if(type == GL_SHORT)  *((short*)pdata + i)         = *((short*)pvalue + i);
        else if(type == GL_BYTE)   *((unsigned char*)pdata + i) = *((unsigned char*)pvalue + i);
    }
}

void Vertex::SetPositionAttribute(void* value, VertexFormat &vf)
{
    string posAttrName = vf.GetPositionAttribute().GetName();
    if(posAttrName != "") SetAttribute(posAttrName, value, vf);
}

void Vertex::SetTexCoordsAttribute(void* value, VertexFormat &vf)
{
    string uvAttrName = vf.GetTexCoordsAttribute().GetName();
    if(uvAttrName != "") SetAttribute(uvAttrName, value, vf);
}

void Vertex::SetNormalsAttribute(void* value, VertexFormat &vf)
{
    string normalsAttrName = vf.GetNormalsAttribute().GetName();
    if(normalsAttrName != "") SetAttribute(normalsAttrName, value, vf);
}

