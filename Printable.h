#ifndef PRINTABLE_H
#define PRINTABLE_H

#include <string>

using namespace std;

class Printable
{
public:

    virtual string ToString() const = 0;

    string operator&(const Printable &p) const;
    string operator&(const string &str) const;
};

#endif // PRINTABLE_H
