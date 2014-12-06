#ifndef DEBUG_H
#define DEBUG_H

#include <GL/gl.h>
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



#define DBG_ASSERT_GL(x) do{\
    x;\
    if(glGetError() > 0) DbgError("There was an openGL error with num: " << glGetError());\
} while(0)

#define DBG_ASSERT_GL_MSG(x, msg) do{\
    x;\
    if(glGetError() > 0) DbgError("Error code: " << glGetError() << ": " << msg);\
} while(0)

#define DBG_ASSERT_GL_RET(x) do{\
    x;\
    if(glGetError() > 0){ DbgError("There was an error with code " << glGetError()); return false;} \
} while(0)

#define DBG_ASSERT_GL_RET_MSG(x, msg) do{\
    x;\
    if(glGetError() < 0){ DbgError("Error code: " << glGetError() << ": " msg); return false;} \
} while(0)



#define DBG_ASSERT(x) do{\
    if(x < 0) DbgError("There was an error");\
} while(0)

#define DBG_ASSERT_MSG(x, msg) do{\
    if(x < 0) DbgError(msg);\
} while(0)

#define DBG_ASSERT_RET(x) do{\
    if(x < 0) { DbgError("There was an error"); return false;}\
} while(0)

#define DBG_ASSERT_RET_MSG(x, msg) do{\
    int err = x;\
    if(err < 0){ DbgError(msg); return false;} \
} while(0)

ostream& operator<<(ostream &log, const Printable &p);

#endif //DEBUG_H
