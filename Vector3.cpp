#include "Vector3.h"

Vector3::Vector3()
{
    x = y = z = 0;
}

Vector3::Vector3(float x, float y, float z)
{
    this->x = x;
    this->y = y;
    this->z = z;
}

float inline Vector3::Mod()
{
    return sqrt(x*x + y*y + z*z);
}

Vector3 Vector3::Norm()
{
    float mod = Mod();
    return Vector3(x/mod, y/mod, z/mod);
}

string Vector3::ToString() const
{
    char buf[256];
    sprintf(buf, "(%f, %f, %f)", x, y, z);
    return string(buf);
}

Vector3& Vector3::operator=(const Vector3 &v)
{
    this->x = v.x;
    this->y = v.y;
    this->z = v.z;
    return *this;
}

Vector3 Vector3::operator+(const Vector3 &v) const
{
    return Vector3(x + v.x, y + v.y, z + v.z);
}

Vector3 Vector3::operator-(const Vector3 &v) const
{
    return Vector3(x - v.x, y - v.y, z - v.z);
}

Vector3 Vector3::operator*(const float a) const
{
    return Vector3(x*a, y*a, z*a);
}

Vector3 Vector3::operator/(const float a) const
{
    return Vector3(x/a, y/a, z/a);
}


bool Vector3::operator==(const Vector3 &v) const
{
    return x == v.x and y == v.y and z == v.z;
}

float Vector3::Distance(const Vector3 &v, const Vector3 &u)
{
    return sqrt((v.x-u.x)*(v.x-u.x) + (v.y-u.y)*(v.y-u.y) + (v.z-u.z)*(v.z-u.z));
}

Vector3 Vector3::Lerp(const Vector3 &from, const Vector3 &to, float f)
{
    return from + (to - from) * f;
}
