#include "include/Vertex.h"

Vertex::Vertex(const VertexFormat &vf)
{
    data = malloc(vf.GetStride());
}

Vertex::~Vertex()
{
    if(data)
    {
        free(data);
        data = 0;
    }
}

void* Vertex::GetAttribute(string name, VertexFormat &vf)
{
    int offset = vf.GetOffsetOf(name);
    if(offset == -1) return 0; //No existe el atributo, return
    return (void*)((char*)data + offset); //(fem cast a char xk la aritmetica de punters sumi de byte en byte(si es void no sap com sumar))
}

void Vertex::SetAttribute(string name, void* value, VertexFormat &vf)
{
    int offset = vf.GetOffsetOf(name);
    if(offset == -1) return; //No existe el atributo, return

    void *p = (void*)((char*)data + offset);
    int type = vf.GetAttribute(name).GetComponentsType();
    if(type == GL_FLOAT)       *((float*)p)         = *((float*)value);
    else if(type == GL_DOUBLE) *((double*)p)        = *((double*)value);
    else if(type == GL_INT)    *((int*)p)           = *((int*)value);
    else if(type == GL_SHORT)  *((short*)p)         = *((short*)value);
    else if(type == GL_BYTE)   *((unsigned char*)p) = *((unsigned char*)value);
}
