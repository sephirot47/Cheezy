#include "Light.h"

Light::Light()
{
    type = LightType;
    radius = 1.0f;
    intensity = 1.0f;
}

void Light::SetRadius(float r)
{
    radius = r;
}

float Light::GetRadius()
{
    return radius;
}

void Light::SetIntensity(float i)
{
    intensity = i;
}

float Light::GetIntensity()
{
    return intensity;
}


void Light::Destroy()
{

}
