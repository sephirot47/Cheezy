#ifndef TRANSFORM_H
#define TRANSFORM_H

#include "include/Component.h"
#include "glm/glm.hpp"

using namespace glm;

class Transform : public Component
{
public:
    vec3 pos;
    vec3 scale;
    quat rot;

    Transform();
    Transform(const Transform &t);
    Transform& operator=(const Transform &t);
    virtual ~Transform();
    void Init(){}
};

#endif // TRANSFORM_H
