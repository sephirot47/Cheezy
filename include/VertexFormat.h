#ifndef VERTEX_FORMAT_H
#define VERTEX_FORMAT_H

#define GL_GLEXT_PROTOTYPES

#include <unordered_map>
#include <GL/gl.h>
#include <GL/glext.h>
#include <string>
#include "include/Debug.h"
#include "include/VertexAttribute.h"
#include "glm/glm.hpp"

using namespace std;

class VertexFormat
{
private:

    unordered_map<string, VertexAttribute> attributes;
    string posName, uvsName, normalsName;
    unsigned int vaoId;

public:

    VertexFormat();
    VertexFormat(VertexFormat &vf);
    ~VertexFormat();

    int GetOffsetOf(string attributeName) const;
    int GetSizeOf(string attributeName) const;
    int GetStride() const;

    void AddAttribute(VertexAttribute &va);
    VertexAttribute GetAttribute(string name);

    void SetPositionAttribute(string attributeName);
    void SetTexCoordsAttribute(string attributeName);
    void SetNormalsAttribute(string attributeName);

    unsigned int CreateVAO(int vboId);
    void DeleteVAO();
};

#endif // VERTEX_FORMAT_H
