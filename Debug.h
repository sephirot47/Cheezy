#ifndef DEBUG_H
#define DEBUG_H

#include <iostream>
#include <string>
#include "Printable.h"

#define DbgWarning(x) Debug::_Warning((x), __LINE__, __FILE__)
#define DbgError(x) Debug::_Error((x), __LINE__, __FILE__)
#define DbgLog(x) Debug::_Log((x))

using namespace std;

namespace Debug
{
    void _Warning(const char* str, int line, const char* file);
    void _Error(const char* str, int line, const char* file);
    void _Log(Printable &p);
    void _Log(const string str);
}

#endif //DEBUG_H
