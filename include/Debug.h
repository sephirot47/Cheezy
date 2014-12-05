#ifndef DEBUG_H
#define DEBUG_H

#include <iostream>
#include <sstream>
#include <string>
#include "Vector3.h"
#include "Printable.h"

using namespace std;

#define DbgWarning(x) do{\
    ostringstream log;\
    log << x;\
    cerr << "Warning(" << __FILE__ << ": " << __FUNCTION__ << ": " << __LINE__ << "): " << log.str() << endl;\
    log.flush();\
} while(0)

#define DbgError(x) do{\
    ostringstream log;\
    log << x;\
    cerr << "Error(" << __FILE__ << ": " << __FUNCTION__ << ": " << __LINE__ << "): " << log.str() << endl;\
    log.flush();\
} while(0)

#define DbgLog(x) do{\
    ostringstream log;\
    log << x;\
    cout << log.str() << endl;\
    log.flush();\
} while(0)

ostream& operator<<(ostream &log, const Printable &p);

#endif //DEBUG_H
