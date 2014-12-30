#ifndef VERTEX_H
#define VERTEX_H

#include <stdio.h>
#include <stdlib.h>
#include "include/VertexFormat.h"

class Vertex
{
private:
    void *data;

public:
    Vertex();
    void Init(const VertexFormat &vf);
    virtual ~Vertex();

    void* GetAttributePointer(string name, VertexFormat &vf);
    bool  HasAttribute(string name, VertexFormat &vf);
    void  SetAttribute(string name, void* value, VertexFormat &vf);
};

#endif // VERTEX_H
