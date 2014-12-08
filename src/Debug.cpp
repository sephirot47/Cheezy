#include "Debug.h"

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
