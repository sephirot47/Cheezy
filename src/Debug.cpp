#include "Debug.h"

string Debug::logFile = "";
ofstream Debug::fileStream;
unsigned char Debug::fileMode = CZ_DBG_LOG | CZ_DBG_WRN | CZ_DBG_ERR;

void Debug::Log(ostringstream &log) 
{
    if (fileMode & CZ_DBG_LOG)
	{
        if (fileStream.is_open()) fileStream << log.str();
    }
    cout << log.str();
}

void Debug::Warning(ostringstream &log) 
{
    if (fileMode & CZ_DBG_WRN)
	{
        if (fileStream.is_open()) fileStream << log.str();
    }
    cerr << log.str();
}

void Debug::Error(ostringstream &log) 
{
    if (fileMode & CZ_DBG_ERR)
	{
        if (fileStream.is_open()) fileStream << log.str();
    }
    cerr << log.str();
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
	if (logFile != "") fileStream.open(logFile,fstream::out);	
}



ostream& operator<<(ostream &log, const Vector2 &v)
{
    log << "(" << v.x << ", " << v.y << ")";
    return log;
}

ostream& operator<<(ostream &log, const Vector3 &v)
{
    log << "(" << v.x << ", " << v.y << ", " << v.z << ")";
    return log;
}

ostream& operator<<(ostream &log, const Quaternion &q)
{
    log << "(" << q.x << ", " << q.y << ", " << q.z << ", " << q.w << ")";
    return log;
}
