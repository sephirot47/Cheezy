#ifndef VERTEX_H
#define VERTEX_H

#include <stdio.h>
#include <stdlib.h>
#include "include/VertexFormat.h"

class Vertex
{
public:
    Vertex();
    virtual ~Vertex();

    void Create(const VertexFormat &vf);
    void *data;

    void* GetAttributePointer(string name, VertexFormat &vf);
    bool  HasAttribute(string name, VertexFormat &vf);
    void  SetAttribute(string name, void* value, VertexFormat &vf);

    void SetPositionAttribute(void* value, VertexFormat &vf);
    void SetTexCoordsAttribute(void* value, VertexFormat &vf);
    void SetNormalsAttribute(void* value, VertexFormat &vf);
};

#endif // VERTEX_H
