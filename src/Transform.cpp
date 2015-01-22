#include "../include/Transform.h"

Transform::Transform()
{
    type = TransformType;
    pos = vec3(0);
    scale = vec3(1);
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

Transform* const Transform::GetDefault()
{
    Transform *t = new Transform();
    return t;
}

Transform::~Transform()
{
}
