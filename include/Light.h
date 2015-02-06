#ifndef LIGHT_H
#define LIGHT_H

#include "include/Component.h"

class Light : public Component
{
private:

    float radius, intensity;

public:

    Light();

    virtual string GetType() const { return type; }

    void SetRadius(float r);
    float GetRadius();

    void SetIntensity(float i);
    float GetIntensity();

    void Destroy();
};

#endif // LIGHT_H
