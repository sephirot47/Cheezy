#ifndef DEBUG_H
#define DEBUG_H

#include <iostream>
#include <sstream>
#include <string>
#include "Printable.h"

#define DbgWarning(x) {\
    cerr << "Warning(" << __FILE__ << ": " << __FUNCTION__ << ": " << __LINE__ << "): " << (x) << endl;\
\}

#define DbgError(x) {\
    cerr << "Error(" << __FILE__ << ": " << __FUNCTION__ << ": " << __LINE__ << "): " << (x) << endl;\
}

#define DbgLog(x) {\
    Debug::Log << x;\
}

typedef ostringstream oss;

using namespace std;

class Debug
{
public:
    static oss Log;
};

#endif //DEBUG_H
