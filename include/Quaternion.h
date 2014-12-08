#ifndef QUATERNION_H
#define QUATERNION_H

#include "Vector3.h"
#include <iostream>
#include <string>
#include <stdio.h>
#include <cmath>


using namespace std;

class Quaternion
{
public:

    float x, y, z, w;

    Quaternion();
    Quaternion(float x, float y, float z, float w);
    Quaternion(Vector3 xyz, int w);
    Quaternion(Vector3 xyz, float w);
    Quaternion(Vector3 xyz, double w);

    ///\brief Returns the quaternion with the following rotation:
    ///       -anglex degrees around x axis
    ///       -angley degrees around y axis
    ///       -anglez degrees around z axis
    static Quaternion Euler(float anglex, float angley, float anglez);

    Quaternion& operator=(const Vector3 &v);
    Quaternion  operator+(const Quaternion &v) const;
    Quaternion  operator-(const Quaternion &v) const;
    Quaternion  operator*(const float a)    const;
    Quaternion  operator/(const float a)    const;

    Quaternion operator* (const Quaternion &q) const;
    Vector3 operator* (const Vector3 &vec);

    bool operator==(const Quaternion &v) const;

    ///\brief Normalizes the quaternion
    void Normalize();

    ///\brief Returns the rotation matrix associated with the quaternion
    void GetRotMatrix(float (&mat)[16]);

    ///\brief Returns the conjugate of the quaternion
    Quaternion GetConjugate() const;

    ///\brief Returns the forward vector of the quaternion
    Vector3 GetForward();

    ///\brief Returns the up vector of the quaternion
    Vector3 GetUp();

    ///\brief Returns the right vector of the quaternion
    Vector3 GetRight();

    ///\brief Returns a quaternion representing a rotation of angle around an axis aligned with axis
    static Quaternion FromAxisAngle(float angle, Vector3 axis);

    //STATICS
    //Devuelve la distancia entre v y u
    static Quaternion Lerp(const Quaternion &from, const Quaternion &to, float f);
};

#endif	
