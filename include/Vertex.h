#ifndef VERTEX_H
#define VERTEX_H

#include <stdio.h>
#include <stdlib.h>
#include "VertexFormat.h"

class Vertex
{
public:
    Vertex(const VertexFormat &vf);
    virtual ~Vertex();

    void *data;

    void* GetAttribute(string name, VertexFormat &vf);
    void  SetAttribute(string name, void* value, VertexFormat &vf);
};

#endif // VERTEX_H
