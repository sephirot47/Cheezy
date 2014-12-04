#ifndef DEBUG_H
#define DEBUG_H

#include <iostream>
#include <sstream>
#include <string>
#include "Vector3.h"
#include "Printable.h"

using namespace std;

#define DbgWarning(x) {\
    cerr << "Warning(" << __FILE__ << ": " << __FUNCTION__ << ": " << __LINE__ << "): " << (x) << endl;\
\}

#define DbgError(x) {\
    cerr << "Error(" << __FILE__ << ": " << __FUNCTION__ << ": " << __LINE__ << "): " << (x) << endl;\
}

#define DbgLog(x) {\
    ostringstream log;\
    log << x;\
    cout << log.str() << endl;\
    log.flush();\
}

ostream& operator<<(ostream &log, const Printable &p);

#endif //DEBUG_H
