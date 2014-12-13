#ifndef DEBUG_H
#define DEBUG_H

#include <GL/gl.h>
#include <GL/glu.h>
#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include "Vector3.h"
#include "Vector2.h"
#include "Quaternion.h"
#include "Time.h"

#define CZ_AUTO_LOG_FILE "cz_auto_log_file"

#define CZ_DBG_LOG 0x01
#define CZ_DBG_WRN 0x02
#define CZ_DBG_ERR 0x04

#define CZ_LOG_DIR "log"


using namespace std;

#define DbgWarning(x) do{\
    ostringstream log;\
    ostringstream wrn;\
    log << x;\
    wrn << "Warning(" << __FILE__ << ": " << __FUNCTION__ << ": " << __LINE__ << "): " << log.str() << endl;\
    Debug::Warning(wrn);\
    log.flush();\
    wrn.flush();\
} while(0)

#define DbgError(x) do{\
    ostringstream log;\
    ostringstream err;\
    log << x;\
    err << "Error(" << __FILE__ << ": " << __FUNCTION__ << ": " << __LINE__ << "): " << log.str() << endl;\
    Debug::Error(err);\
    log.flush();\
    err.flush();\
} while(0)

#define DbgLog(x) do{\
    ostringstream log;\
    log << x << endl;\
   /*Debug::Log(log);*/\
    log.flush();\
} while(0)


#define DBG_ASSERT_GL(x) do{\
    x;\
    int error = glGetError();\
    if(error > 0) DbgError("GL Error('" << gluErrorString(error)  << "')");\
} while(0)

#define DBG_ASSERT_GL_MSG(x, msg) do{\
    x;\
    int error = glGetError();\
    if(error > 0) DbgError("GL Error('" << gluErrorString(error) << "')" << ": " << msg);\
} while(0)

#define DBG_ASSERT_GL_RET(x) do{\
    x;\
    int error = glGetError();\
    if(error > 0){ DbgError("GL Error('" << gluErrorString(error) << "')"); return false;} \
} while(0)

#define DBG_ASSERT_GL_RET_MSG(x, msg) do{\
    x;\
    int error = glGetError();\
    if(error > 0){ DbgError("GL Error('" << gluErrorString(error)  << "')" << ": " << msg); return false;} \
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

class Debug
{
private:
    static string logFile;
    static ofstream fileStream;

public:
    static unsigned char fileMode; 
    static void SetFile(string filepath);
    static void Log(ostringstream &log);
    static void Warning(ostringstream &log);
    static void Error(ostringstream &log);
};

#endif //DEBUG_H
