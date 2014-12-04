#ifndef DEBUG_H
#define DEBUG_H

#include <iostream>
#include <sstream>
#include <string>
#include "Vector3.h"
#include "Printable.h"

#define DbgWarning(x) {\
    cerr << "Warning(" << __FILE__ << ": " << __FUNCTION__ << ": " << __LINE__ << "): " << (x) << endl;\
\}

#define DbgError(x) {\
    cerr << "Error(" << __FILE__ << ": " << __FUNCTION__ << ": " << __LINE__ << "): " << (x) << endl;\
}

#define DbgLog(x) {\
    Log log = Log();\
    log << x;\
    cout << log.str() << endl;\
    log.flush();\
}

using namespace std;

class Log : public ostringstream
{
public:
    Log() {}
    Log& operator<<(const Printable &p)
    {
       *this << p.ToString();
       return *this;
    }
};

#endif //DEBUG_H
