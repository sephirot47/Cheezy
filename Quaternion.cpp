#include "Quaternion.h"

Quaternion::Quaternion()
{
    x = y = z = w = 0;
}

Quaternion::Quaternion(float x, float y, float z, float w)
{
    this->x = x;
    this->y = y;
    this->z = z;
    this->w = w;
}

Quaternion::Quaternion(Vector3 xyz, int w)
{
    this->x = xyz.x;
    this->y = xyz.y;
    this->z = xyz.z;
    this->w = (float)w;
}

Quaternion::Quaternion(Vector3 xyz, float w)
{
    this->x = xyz.x;
    this->y = xyz.y;
    this->z = xyz.z;
    this->w = w;
}

Quaternion::Quaternion(Vector3 xyz, double w)
{
    this->x = xyz.x;
    this->y = xyz.y;
    this->z = xyz.z;
    this->w = (float)w;
}

string Quaternion::ToString() const
{
    char buf[256];
    sprintf(buf, "(%f, %f, %f, %f)", x, y, z, w);
    return string(buf);
}

Quaternion Quaternion::operator+(const Quaternion &v) const
{
    return Quaternion(x + v.x, y + v.y, z + v.z, w + v.w);
}

Quaternion Quaternion::operator-(const Quaternion &v) const
{
    return Quaternion(x - v.x, y - v.y, z - v.z, w - v.w);
}

Quaternion Quaternion::operator*(const float a) const
{
    return Quaternion(x*a, y*a, z*a, w*a);
}

Quaternion Quaternion::operator/(const float a) const
{
    return Quaternion(x/a, y/a, z/a, w/a);
}


bool Quaternion::operator==(const Quaternion &v) const
{
    return x == v.x and y == v.y and z == v.z and w == v.w; 
}

float Quaternion::Distance(const Quaternion &v, const Quaternion &u)
{
    return sqrt((v.x-u.x)*(v.x-u.x) + (v.y-u.y)*(v.y-u.y) + (v.z-u.z)*(v.z-u.z));
}

Quaternion Quaternion::Lerp(const Quaternion &from, const Quaternion &to, float f)
{
    return from + (to - from) * f;
}

void Quaternion::GetRotMatrix(float (&mat)[16]) const 
{ 
    float x2 = x * x;
    float y2 = y * y;
    float z2 = z * z;
    float xy = x * y;
    float xz = x * z;
    float yz = y * z;
    float wx = w * x;
    float wy = w * y;
    float wz = w * z;

    mat[0] = 1.0f - 2.0f * (y2 + z2);
    mat[1] = 2.0f * (xy - wz);
    mat[2] = 2.0f * (xz + wy);
    mat[3] = 0.0f;
    mat[4] = 2.0f * (xy + wz);
    mat[5] = 1.0f - 2.0f * (x2 + z2);
    mat[6] = 2.0f * (yz - wx);
    mat[7] = 0.0f;
    mat[8] = 2.0f * (xz - wy);
    mat[9] = 2.0f * (yz + wx);
    mat[10] = 1.0f - 2.0f * (x2 + y2);
    mat[11] = mat[12] = mat[13] = mat[14] = mat[15] = 0.0f;  
}

