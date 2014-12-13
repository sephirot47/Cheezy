#ifndef DEBUG_H
#define DEBUG_H

#include <GL/gl.h>
#include <iostream>
#include <sstream>
#include <string>
#include "Vector3.h"
#include "Vector2.h"
#include "Quaternion.h"


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
    if(glGetError() > 0) DbgError("GL Error code: " << glGetError());\
} while(0)

#define DBG_ASSERT_GL_MSG(x, msg) do{\
    x;\
    if(glGetError() > 0) DbgError("GL Error code: " << glGetError() << ": " << msg);\
} while(0)

#define DBG_ASSERT_GL_RET(x) do{\
    x;\
    if(glGetError() > 0){ DbgError("GL Error code: " << glGetError()); return false;} \
} while(0)

#define DBG_ASSERT_GL_RET_MSG(x, msg) do{\
    x;\
    if(glGetError() > 0){ DbgError("GL Error code: " << glGetError() << ": " << msg); return false;} \
} while(0)



#define DBG_ASSERT(x) do{\
    if((x) < 0) DbgError("There was an error");\
} while(0)

#define DBG_ASSERT_MSG(x, msg) do{\
    if((x) < 0) DbgError(msg);\
} while(0)

#define DBG_ASSERT_RET(x) do{\
    if((x) < 0) { DbgError("There was an error"); return false;}\
} while(0)

#define DBG_ASSERT_RET_MSG(x, msg) do{\
    if((x) < 0){ DbgError(msg); return false;} \
} while(0)


//OSTREAM OPERATORS //////////////////////////////////
ostream& operator<<(ostream &log, const Vector3 &v);
ostream& operator<<(ostream &log, const Quaternion &q);
ostream& operator<<(ostream &log, const Vector2 &v);

#endif //DEBUG_H
