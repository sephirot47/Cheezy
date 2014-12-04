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
/*
string operator&(const Printable &p1, const Printable &p2);
string operator&(const Printable &p, const string &str);
string operator&(const string &str, const Printable &p);
string operator&(const string &str1, const string &str2);

string operator&(const float &f, const Printable &p);
string operator&(const Printable &p, const float &f);
string operator&(const string &str1, const float &f);
string operator&(const float &f, const string &str);

string operator&(const int &a, const string &str);
string operator&(const string &str, const int &a);
string operator&(const int &a, const Printable &str);
string operator&(const Printable &str, const int &a);
*/
#endif // PRINTABLE_H
