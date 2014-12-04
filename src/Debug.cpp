#include "Debug.h"

ostream& operator<<(ostream &log, const Printable &p)
{
   log << p.ToString();
   return log;
}
