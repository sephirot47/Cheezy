#include "include/Quaternion.h"

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
    this->x = x;
    this->y = y;
    this->z = z;
    this->w = (float)w;
}

Quaternion::Quaternion(Vector3 xyz, int w)
{
    this->x = x;
    this->y = y;
    this->z = z;
    this->w = (float)w;
}

Quaternion::Quaternion(Vector3 xyz, float w)
{
    this->x = x;
    this->y = y;
    this->z = z;
    this->w = w;
}

Quaternion::Quaternion(Vector3 xyz, double w)
{
    this->x = x;
    this->y = y;
    this->z = z;
    this->w = (float)w;
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

Vector3 Quaternion::operator* (const Vector3 &vec)
{
    float mat[16];
    GetRotMatrix(mat);

    float v0 = mat[0] * vec.x + mat[4] * vec.y + mat[8]  * vec.z;
    float v1 = mat[1] * vec.x + mat[5] * vec.y + mat[9]  * vec.z;
    float v2 = mat[2] * vec.x + mat[6] * vec.y + mat[10] * vec.z;

    return Vector3(v0, v1, v2);
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
}

Vector3 Quaternion::GetForward()
{
    return GetConjugate() * Vector3(0, 0, 1);
}

Vector3 Quaternion::GetUp()
{
    return GetConjugate() * Vector3(0, 1, 0);
}

Vector3 Quaternion::GetRight()
{
    return GetConjugate() * Vector3(1, 0, 0);
}

Quaternion Quaternion::FromAxisAngle(float angle, Vector3 axis)
{
    float half_sin = sin(0.5f * angle);
    float half_cos = cos(0.5f * angle);
    return Quaternion(half_cos, half_sin * axis.x, half_sin * axis.y, half_sin * axis.z);
}
