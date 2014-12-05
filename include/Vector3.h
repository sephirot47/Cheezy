#ifndef VECTOR3_H
#define VECTOR3_H

#include <iostream>
#include <string>
#include <stdio.h>
#include <cmath>
#include "Printable.h"

using namespace std;

class Vector3 : public Printable
{
public:

    float x, y, z;

    Vector3();
    Vector3(int x, int y, int z);
    Vector3(float x, float y, float z);
    Vector3(double x, double y, double z);

    ///\brief Returns the normalized Vector3
    Vector3 Norm() const;

    ///\brief Returns the magnitude of the Vector3
    float Magnitude() const;

    ///\brief Converts the Vector3 to a String
    string ToString() const; //Devuelve el string "(x,y,z)"

    Vector3& operator=(const Vector3 &v);
    Vector3  operator+(const Vector3 &v) const;
    Vector3  operator-(const Vector3 &v) const;
    Vector3  operator*(const float a)    const; //Multiplica x,y,z por un entero a
    Vector3  operator/(const float a)    const; //Divide x,y,z entre un entero a

    bool operator==(const Vector3 &v) const;

    //STATICS
    //Devuelve la distancia entre v y u
    ///\brief Returns the distance between u and v
    static float Distance(const Vector3 &u, const Vector3 &v);
    ///\brief Returns the dot product of u and v
    static float Dot(const Vector3 &u, const Vector3 &v);
    ///\brief Returns the cross product of u and v
    static Vector3 Cross(const Vector3 &u, const Vector3 &v);
    ///\brief Makes a linear interpolation from vfrom to vto
    ///       If f==0, returns vFrom
    ///       If f==1 returns vto
    ///       Else, returns a linear interpolation from vfrom to vto
    static Vector3 Lerp(const Vector3 &vfrom, const Vector3 &vto, float f);
};

#endif // VECTOR3_H
