#include "Vertex.h"

Vertex::Vertex()
{
}

Vertex::Vertex(float posx, float posy, float posz)
{
    this->pos = Vector3(posx, posy, posz);
}

Vertex::Vertex(Vector3 pos)
{
    this->pos = pos;
}
