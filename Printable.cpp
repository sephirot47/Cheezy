#include "Printable.h"

string Printable::operator&(const Printable& p) const
{
    return this->ToString() + " " + p.ToString();
}

string Printable::operator&(const string &str) const
{
    return this->ToString() + str;
}
