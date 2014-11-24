#include "Debug.h"

using namespace std;

void Debug::Warning(const string &str)
{
    cerr << "Warning: " << str << endl;
}

void Debug::Error(const string &str)
{
    cerr << "Error: " << str << endl;
}

void Debug::Log(Printable &p)
{
    cout << p.ToString() << endl;
}

void Debug::Log(const string str)
{
    cout << str << endl;
}




