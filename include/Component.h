#ifndef COMPONENT_H
#define COMPONENT_H

#include <string>

using namespace std;

class Component
{
public:

    string type;
    Component(){}
    virtual void Init() = 0;
};

#endif // COMPONENT_H
