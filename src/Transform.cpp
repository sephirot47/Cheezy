#include "include/Transform.h"

Transform::Transform()
{
    type = "Transform";
    pos = scale = vec3(0);
    rot = quat();
}

Transform::Transform(const Transform &t)
{
    type = t.type;
    pos = t.pos;
    rot = t.rot;
    scale = t.scale;
}

Transform &Transform::operator=(const Transform &t)
{
    if(this == &t) return *this;
    type = t.type;
    pos = t.pos;
    rot = t.rot;
    scale = t.scale;
    return *this;
}


Transform::~Transform()
{
}
