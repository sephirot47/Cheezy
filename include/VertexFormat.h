#ifndef VERTEX_FORMAT_H
#define VERTEX_FORMAT_H

#define GL_GLEXT_PROTOTYPES

#include <unordered_map>
#include <GL/gl.h>
#include <GL/glext.h>
#include <string>
#include <vector>

#include "include/Debug.h"
#include "include/Material.h"
#include "include/VertexAttribute.h"
#include "glm/glm.hpp"

using namespace std;

class VertexFormat
{
private:

    unordered_map<string, VertexAttribute> attributes;
    vector<string> insertionOrder;
    string posName, uvsName, normalsName;
    int attributesCount;
    unsigned int vaoId;

public:

    VertexFormat();
    VertexFormat(const VertexFormat &vf);
    VertexFormat& operator=(const VertexFormat &vf);
    ~VertexFormat();

    static void GetDefault(VertexFormat &vf);

    int GetOffsetOf(string attributeName) const;
    int GetOffsetOf(int i) const;
    int GetSizeOf(string attributeName) const;
    int GetSizeOf(int i) const;
    int GetStride() const;
    int GetAttributesNum() const;

    void AddAttribute(const VertexAttribute &va);
    VertexAttribute GetAttribute(int i) const;
    VertexAttribute GetAttribute(string name) const;

    void SetPositionAttributeName(string attributeName);
    void SetTexCoordsAttributeName(string attributeName);
    void SetNormalsAttributeName(string attributeName);

    VertexAttribute GetPositionAttribute() const;
    VertexAttribute GetTexCoordsAttribute() const;
    VertexAttribute GetNormalsAttribute() const;

    int CreateVAO(int vboId);
    int CreateVAOForMaterial(int vboId, const Material &material);
    void DeleteVAO();
};

#endif // VERTEX_FORMAT_H
