#include "Quaternion.h"
#include "Debug.h"

Quaternion::Quaternion()
{
    x = y = z = w = 0.0f;
}

Quaternion Quaternion::Euler(float anglex, float angley, float anglez)
{
    anglex *= M_PI/180.0f;
    angley *= M_PI/180.0f;
    anglez *= M_PI/180.0f;

    double angle = anglex * 0.5;
    const double sr = sin(angle);
    const double cr = cos(angle);

    angle = angley * 0.5;
    const double sp = sin(angle);
    const double cp = cos(angle);

    angle = anglez * 0.5;
    const double sy = sin(angle);
    const double cy = cos(angle);

    const double cpcy = cp * cy;
    const double spcy = sp * cy;
    const double cpsy = cp * sy;
    const double spsy = sp * sy;

    Quaternion q;
    q.x = (float)(sr*cpcy - cr * spsy);
    q.y = (float)(cr*spcy + sr * cpsy);
    q.z = (float)(cr*cpsy - sr * spcy);
    q.w = (float)(cr*cpcy + sr * spsy);
    q.Normalize();
    return q;
}

Quaternion::Quaternion(float x, float y, float z, float w)
{
    Vector3 xyz(x,y,z);
    xyz = xyz.Norm();
    this->x = xyz.x;
    this->y = xyz.y;
    this->z = xyz.z;
    this->w = (float)w;
    Normalize();
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
    /*
	return Quaternion(w * q.x + x * q.w + y * q.z - z * q.y,
	                  w * q.y + y * q.w + z * q.x - x * q.z,
	                  w * q.z + z * q.w + x * q.y - y * q.x,
	                  w * q.w - x * q.x - y * q.y - z * q.z);
                      */
    return Quaternion(w * q.x + x * q.w + y * q.z - z * q.y,
                      w * q.y + y * q.w + z * q.x - x * q.z,
                      w * q.z + z * q.w + x * q.y - y * q.x,
                      w * q.w - x * q.x - y * q.y - z * q.z);
}

Vector3 Quaternion::operator* (const Vector3 &vec)
{
    /*
    Vector3 uv, uuv;
    Vector3 qvec(x,y,z);
    uv = Vector3::Cross(qvec,vec);
    uuv = Vector3::Cross(qvec,uv);
    uv = uv * (2.0f * w);
    uuv = uuv * 2.0f;

    return vec + uv + uuv;
    */
    float mat[16];
    GetRotMatrix(mat);

    float v0 = mat[0] * vec.x + mat[4] * vec.y + mat[8]  * vec.z;
    float v1 = mat[1] * vec.x + mat[5] * vec.y + mat[9]  * vec.z;
    float v2 = mat[2] * vec.x + mat[6] * vec.y + mat[10] * vec.z;

    return Vector3(v0, v1, v2);

/*
    Quaternion resQuat, vecQuat(vec,0);

    resQuat = vecQuat * GetConjugate();
    resQuat = *this * resQuat;

    return (Vector3(resQuat.x, resQuat.y, resQuat.z));
    */

}

bool Quaternion::operator==(const Quaternion &v) const
{
    return x == v.x and y == v.y and z == v.z and w == v.w; 
}

Quaternion Quaternion::GetConjugate() const
{
	return Quaternion(-x, -y, -z, w);
}

void Quaternion::Normalize() {
    float mag = sqrt(x*x+y*y+z*z+w*w);
    x /= mag;
    y /= mag;
    z /= mag;
    w /= mag;
}

void Quaternion::GetRotMatrix(float (&mat)[16])
{
    Normalize();
    mat[0] = 1.0f - 2.0f * y*y - 2.0f * z*z;
    mat[1] = 2.0f * x*y + 2.0f * z*w;
    mat[2] = 2.0f * x*z - 2.0f * y*w;
    mat[3] = 0.0f;

    mat[4] = 2.0f * x*y - 2.0f * z*w;
    mat[5] = 1.0f - 2.0f * x*x - 2.0f * z*z;
    mat[6] = 2.0f * z*y + 2.0f * x*w;
    mat[7] = 0.0f;

    mat[8] = 2.0f * x*z + 2.0f * y*w;
    mat[9] = 2.0f * z*y - 2.0f * x*w;
    mat[10] = 1.0f - 2.0f * x*x - 2.0 * y*y;
    mat[11] = 0.0f;

    mat[12] = mat[13] = mat[14] = 0.0f;
    mat[15] = 1.0f;

    /*
    mat[0] = 1.0f - 2.0f * (y2 + z2);
    mat[4] = 2.0f * (xy - wz);
    mat[8] = 2.0f * (xz + wy);
    mat[12] = 0.0f;

    mat[1] = 2.0f * (xy + wz);
    mat[5] = 1.0f - 2.0f * (x2 + z2);
    mat[9] = 2.0f * (yz - wx);
    mat[13] = 0.0f;

    mat[2] = 2.0f * (xz - wy);
    mat[6] = 2.0f * (yz + wx);
    mat[10] = 1.0f - 2.0f * (x2 + y2);
    mat[14] = 0.0f;

    mat[3] = mat[7] = mat[11] = 0.0f;
    mat[15] = 1.0f;
    */
}

