#ifndef PRINTABLE_H
#define PRINTABLE_H

#include <string.h>
#include <stdio.h>
#include <string>

using namespace std;

class Printable
{
public:
    virtual string ToString() const = 0;
};

#endif // PRINTABLE_H
