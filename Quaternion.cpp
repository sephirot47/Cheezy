#include "Quaternion.h"
#include "Debug.h"

Quaternion::Quaternion()
{
    x = y = z = w = 0.0f;
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
    xyz = xyz.Norm();
    this->x = xyz.x;
    this->y = xyz.y;
    this->z = xyz.z;
    this->w = (float)w;
}

Quaternion::Quaternion(Vector3 xyz, float w)
{
    xyz = xyz.Norm();
    this->x = xyz.x;
    this->y = xyz.y;
    this->z = xyz.z;
    this->w = w;
}

Quaternion::Quaternion(Vector3 xyz, double w)
{
    xyz = xyz.Norm();
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

Quaternion Quaternion::operator* (const Quaternion &q) const
{
	return Quaternion(w * q.x + x * q.w + y * q.z - z * q.y,
	                  w * q.y + y * q.w + z * q.x - x * q.z,
	                  w * q.z + z * q.w + x * q.y - y * q.x,
	                  w * q.w - x * q.x - y * q.y - z * q.z);
}



Vector3 Quaternion::operator* (const Vector3 &v)
{
	Vector3 u(this->x, this->y, this->z);

    // Extract the scalar part of the quaternion
    float s = this->w;

    // Do the math
    Vector3 vprime = u * (2.0f * Vector3::Dot(u, v))
          + v * (s*s - Vector3::Dot(u, u))
          + Vector3::Cross(u, v) * (2.0f * s);
          return vprime;

    /*Vector3 vn(v);
    vn = vn.Norm();
    DbgLog(vn & GetConjugate());
    Quaternion vecQuat, resQuat;
    vecQuat.x = vn.x;
    vecQuat.y = vn.y;
    vecQuat.z = vn.z;
    vecQuat.w = 0.0f;
 
    resQuat = vecQuat * GetConjugate();
    resQuat = *this * resQuat;
 
    return (Vector3(resQuat.x, resQuat.y, resQuat.z));*/
}

bool Quaternion::operator==(const Quaternion &v) const
{
    return x == v.x and y == v.y and z == v.z and w == v.w; 
}

Quaternion Quaternion::Lerp(const Quaternion &from, const Quaternion &to, float f)
{
    return from + (to - from) * f;
}

Quaternion Quaternion::GetConjugate()
{
	return Quaternion(-x, -y, -z, w);
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
    mat[11] = 0.0f;
    
    mat[12] = mat[13] = mat[14] = mat[15] = 0.0f;  
}

