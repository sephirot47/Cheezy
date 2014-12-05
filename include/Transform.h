#ifndef TRANSFORM_H
#define TRANSFORM_H

#include "Component.h"
#include "Quaternion.h"
#include "Vector3.h"

class Transform : public Component
{
public:
    Vector3 pos;
    Quaternion rot;
    Vector3 scale;

    Transform();
    void Init(){}
};

#endif // TRANSFORM_H
