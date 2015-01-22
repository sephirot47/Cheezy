#ifndef BINDABLE_H
#define BINDABLE_H

class Bindable
{
public:
    virtual void Bind() const = 0;
    virtual void UnBind() const = 0;
};

#endif // BINDABLE_H
