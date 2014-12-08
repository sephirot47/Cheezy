#ifndef VERTEX_H
#define VERTEX_H

#include "Vector3.h"

class Vertex
{
public:

    Vertex();
    Vertex(float posx, float posy, float posz);
    Vertex(Vector3 pos);
    Vector3 pos;
};

#endif // VERTEX_H
