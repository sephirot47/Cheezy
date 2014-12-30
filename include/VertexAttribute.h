#ifndef VERTEXATTRIBUTE_H
#define VERTEXATTRIBUTE_H

#include <GL/gl.h>
#include <string>
#include "include/Debug.h"

using namespace std;

class VertexAttribute
{
private:

    string name;
    int componentsSize, componentsNum, componentsType;

public:

    VertexAttribute();
    VertexAttribute(string name, int nComponents, int componentsType);

    string GetName() const;
    int GetComponentsCount() const;
    int GetComponentsType() const;
    int GetSize() const;
};

#endif // VERTEXATTRIBUTE_H
