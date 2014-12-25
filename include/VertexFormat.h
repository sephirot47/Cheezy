#ifndef VERTEX_FORMAT_H
#define VERTEX_FORMAT_H

#define GL_GLEXT_PROTOTYPES

#include <unordered_map>
#include <GL/gl.h>
#include <GL/glext.h>
#include <string>
#include "Debug.h"
#include "VertexAttribute.h"
#include "glm/glm.hpp"

using namespace std;

class VertexFormat
{
private:

    unordered_map<string, VertexAttribute*> attributes;
    string posName, uvsName, normalsName;
    unsigned int vaoId;

public:

    VertexFormat();

    static VertexFormat Default;

    int GetOffsetOf(string attributeName) const;
    int GetSizeOf(string attributeName) const;
    int GetStride() const;

    void AddAttribute(VertexAttribute &va);
    void AddAttribute(VertexAttribute *va);
    void DeleteAttribute(VertexAttribute &va);
    void DeleteAttribute(VertexAttribute *va);

    bool HasAttributeOfType(int type) const;
    VertexAttribute GetAttribute(string name);


    void SetPositionAttribute(string attributeName);
    void SetTexCoordsAttribute(string attributeName);
    void SetNormalsAttribute(string attributeName);

    unsigned int CreateVAO();
    void DeleteVAO();
};

#endif // VERTEX_FORMAT_H
