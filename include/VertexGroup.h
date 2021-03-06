#ifndef VERTEXGROUP_H
#define VERTEXGROUP_H

#include "include/Vertex.h"
#include "include/VertexFormat.h"
#include "include/VertexAttribute.h"

class VertexGroup
{
private:
    int vertexCount;
    VertexFormat *vertexFormat;

public:

    void *data;
    VertexGroup();
    VertexGroup(const VertexGroup &vg);
    VertexGroup& operator=(const VertexGroup &vg);
    virtual ~VertexGroup();

    void Init(const VertexGroup& vg);
    void Init(int vertexCount);
    void Init(const VertexFormat &vf);
    void Init(int vertexCount, const VertexFormat &vf);
    void Init(const vector<Vertex>& vertices);

    void SetAttribute(string attributeName, void *pvalue, int vertexIndex);

    Vertex* GetVertexPointer(int vertexIndex) const;
    void*   GetAttributePointer(string attributeName, int vertexIndex) const;

    int   GetVertexCount() const;
    void* GetRawData() const;
    VertexFormat GetVertexFormat() const;

    void   SetVertex(int vertexIndex, const  Vertex &v);
    Vertex GetVertex(int vertexIndex) const;
};

#endif // VERTEXGROUP_H
