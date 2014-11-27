#include "Debug.h"


using namespace std;

void Debug::_Warning(const char* str, int line, const char* file)
{
    cerr << "Warning(" << file << ":" << line << "): " << str << endl;
}

void Debug::_Error(const char* str, int line, const char* file)
{
    cerr << "Error(" << file << ":" << line << "): " << str << endl;
}

void Debug::_Log(Printable &p)
{
    cout << p.ToString() << endl;
}

void Debug::_Log(const string str)
{
    cout << str << endl;
}



