#ifndef VERTEX_H
#define VERTEX_H

#include "Vector2.h"
#include "Vector3.h"

#define CZ_VERTEX_ATTR_VECTOR3 0
#define CZ_VERTEX_ATTR_UV 1

class Vertex
{
public:

    Vertex();
    Vertex(float posx, float posy, float posz);
    Vertex(Vector3 pos);

    Vector3 pos;
    Vector2 uv;
};

#endif // VERTEX_H
