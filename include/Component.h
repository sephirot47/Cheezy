#ifndef COMPONENT_H
#define COMPONENT_H

#include <string>

using namespace std;

class Component
{
public:

    string type;
    Component(){}
    virtual string GetType() const = 0;
    virtual void Destroy() = 0;
};

#endif // COMPONENT_H
