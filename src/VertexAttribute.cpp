#include "include/VertexAttribute.h"

VertexAttribute::VertexAttribute()
{
    name = "";
    componentsType = GL_FLOAT;
    componentsNum = componentsSize = 0;
}

VertexAttribute::VertexAttribute(const VertexAttribute &va)
{
    name = va.name;
    componentsType = va.componentsType;
    componentsNum = va.componentsNum;
    componentsSize = va.componentsSize;
}

VertexAttribute &VertexAttribute::operator=(const VertexAttribute &va)
{
    if(this == &va) return *this;
    name = va.name;
    componentsType = va.componentsType;
    componentsNum = va.componentsNum;
    componentsSize = va.componentsSize;
    return *this;
}

VertexAttribute::VertexAttribute(string name, int nComponents, int componentsType)
{
    bool correct = true;
    if(componentsType == GL_FLOAT) componentsSize = 4;
    else if(componentsType == GL_SHORT) componentsSize = 1;
    else
    {
        DbgError("Not recognized vertex attribute type!");
        correct = false;
        componentsSize = 0;
    }

    if(correct)
    {
        if(nComponents > 4 or nComponents < 0)
        {
            componentsSize = 0;
            DbgError("A vertex attribute can have more than 4 elements or less than 0.");
        }
        else
        {
            this->name = name;
            this->componentsNum = nComponents;
            this->componentsType = componentsType;
        }
    }
}


string VertexAttribute::GetName() const
{
    return name;
}

int VertexAttribute::GetComponentsCount() const
{
    return componentsNum;
}

int VertexAttribute::GetComponentsType() const
{
    return componentsType;
}

int VertexAttribute::GetSize() const
{
    return componentsNum * componentsSize;
}
