#include "include/Debug.h"

string Debug::logFile;
ofstream Debug::fileStream;
unsigned int Debug::fileMode = DbgModeLog | DbgModeWarning | DbgModeError;
unsigned int Debug::outputMode = DbgModeFile | DbgModeTerm;

void Debug::Log(ostringstream &log) 
{
    if (outputMode & DbgModeFile and fileMode & DbgModeLog)
	{
        if (fileStream.is_open()) fileStream << log.str();
    }

    if (outputMode & DbgModeTerm)
    {
    	cout << log.str();
	}
}

void Debug::Warning(ostringstream &log) 
{
    if (outputMode & DbgModeFile and fileMode & DbgModeWarning)
	{
        if (fileStream.is_open()) fileStream << log.str();
    }

    if (outputMode & DbgModeTerm)
    {
    	cerr << log.str();
    }
}

void Debug::Error(ostringstream &log) 
{
    if (outputMode & DbgModeFile and fileMode & DbgModeError)
	{
        if (fileStream.is_open()) fileStream << log.str(); 
    }

    if (outputMode & DbgModeTerm)
    {
    	cerr << log.str();
    }
}

void Debug::SetFile(string filepath) 
{
	if (filepath == CZ_AUTO_LOG_FILE) 
	{
		string dbg = CZ_LOG_DIR;
		dbg.append("/");
		dbg.append(Time::GetDateStr());
		dbg.append(".log");
		filepath = dbg;
		cerr << "Saving log to: " << filepath << endl;
	}
	logFile = filepath;
	if (fileStream.is_open()) fileStream.close();
        fileStream.open(logFile,fstream::out);
}


ostream& operator<<(ostream &log, const vec2 &v)
{
    log << "(" << v.x << ", " << v.y << ")";
    return log;
}

ostream& operator<<(ostream &log, const vec3 &v)
{
    log << "(" << v.x << ", " << v.y << ", " << v.z << ")";
    return log;
}

ostream& operator<<(ostream &log, const quat &q)
{
    log << "(" << q.x << ", " << q.y << ", " << q.z << ", " << q.w << ")";
    return log;
}
