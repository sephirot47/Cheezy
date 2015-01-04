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
    Vertex(const Vertex &v, const VertexFormat &vf);
    Vertex& operator=(const Vertex &v);
    void Init(const VertexFormat &vf);
    virtual ~Vertex();

    void* GetAttributePointer(string name, const VertexFormat &vf) const;
    bool  HasAttribute(string name, const VertexFormat &vf) const;
    void  SetAttribute(string name, void* value, const VertexFormat &vf);
};

#endif // VERTEX_H
