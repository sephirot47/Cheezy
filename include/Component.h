#ifndef COMPONENT_H
#define COMPONENT_H

#include <string>

using namespace std;

enum ComponentType
{
    MeshType = 1,
    LightType = 2,
    TransformType = 3
};

class Component
{
public:

    ComponentType type;
    Component(){}
    virtual ComponentType GetType() const = 0;
    virtual void Destroy() = 0;
};

#endif // COMPONENT_H
