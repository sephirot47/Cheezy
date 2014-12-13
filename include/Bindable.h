#ifndef BINDABLE_H
#define BINDABLE_H

class Bindable
{
public:
    virtual void Bind() = 0;
    virtual void UnBind() = 0;
};

#endif // BINDABLE_H
