#include "include/Quaternion.h"

Quaternion::Quaternion() : quat()
{
}

Quaternion::Quaternion(quat q) : quat(q)
{
}

vec3 Quaternion::GetForward() const { return (*this) * vec3(0, 0, -1); }
vec3 Quaternion::GetUp() const { return (*this) * vec3(0, 1, 0); }
vec3 Quaternion::GetRight() const { return (*this) * vec3(1, 0, 0); }

Quaternion Quaternion::Normalized() const
{
    float l = this->length();
    Quaternion q(*this);
    q.x /= l;
    q.y /= l;
    q.z /= l;
    q.w /= l;
    return q;
}

Quaternion Quaternion::AxisAngle(const vec3 &axis, float degrees)
{
    return angleAxis(degrees, axis);
}

Quaternion Quaternion::FromAxes(const vec3& xAxis, const vec3& yAxis, const vec3& zAxis)
{
    mat3 kRot;
    kRot[0] = xAxis;
    kRot[1] = yAxis;
    kRot[2] = zAxis;
    return Quaternion(quat_cast(kRot));
}

Quaternion Quaternion::FromTo(const vec3 &from, const vec3 &to)
{
    Quaternion q;
    vec3 a = cross(from, to);
    q.x = a.x; q.y = a.y; q.z = a.z;
    float d = dot(from, to);
    if(abs(d) > 0.99999f) return Quaternion(); //return identity(do nothing)
    q.w = sqrt(from.length() * from.length() * to.length() * to.length()) + d;
    return q.Normalized();
}
