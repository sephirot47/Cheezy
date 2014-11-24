#ifndef DEBUG_H
#define DEBUG_H

#include <iostream>
#include <string>
#include "Printable.h"

using namespace std;

namespace Debug
{
    void Warning(const string &str);
    void Error(const string &str);
    void Log(Printable &p);
    void Log(const string str);
}

#endif // DEBUG_H
