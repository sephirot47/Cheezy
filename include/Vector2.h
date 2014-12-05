#ifndef Vector2_H
#define Vector2_H

#include <iostream>
#include <stdio.h>
#include <cmath>
#include "Printable.h"

using namespace std;

class Vector2 : public Printable
{
public:

    float x, y;

    Vector2();
    Vector2(int x, int y);
    Vector2(float x, float y);
    Vector2(double x, double y);

    ///\brief Returns the normalized Vector2
    Vector2 Norm() const;

    ///\brief Returns the magnitude of the Vector2
    float Magnitude() const;

    ///\brief Converts the Vector2 to a String
    string ToString() const; //Devuelve el string "(x,y,z)"

    Vector2& operator=(const Vector2 &v);
    Vector2  operator+(const Vector2 &v) const;
    Vector2  operator-(const Vector2 &v) const;
    Vector2  operator*(const float a)    const; //Multiplica x,y,z por un entero a
    Vector2  operator/(const float a)    const; //Divide x,y,z entre un entero a

    bool operator==(const Vector2 &v) const;

    //STATICS
    //Devuelve la distancia entre v y u
    ///\brief Returns the distance between u and v
    static float Distance(const Vector2 &u, const Vector2 &v);
    ///\brief Makes a linear interpolation from vfrom to vto
    ///       If f==0, returns vFrom
    ///       If f==1 returns vto
    ///       Else, returns a linear interpolation from vfrom to vto
    static Vector2 Lerp(const Vector2 &vfrom, const Vector2 &vto, float f);
};

#endif // Vector2_H
