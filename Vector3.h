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
    Vector3(float x, float y, float z);

    Vector3 Norm();   //Devuelve el vector normalizado

    float Mod(); //Devuelve el modulo del vector

    string ToString() const; //Devuelve el string "(x,y,z)"

    Vector3& operator=(const Vector3 &v);
    Vector3  operator+(const Vector3 &v) const;
    Vector3  operator-(const Vector3 &v) const;
    Vector3  operator*(const float a)    const; //Multiplica x,y,z por un entero a
    Vector3  operator/(const float a)    const; //Divide x,y,z entre un entero a

    bool operator==(const Vector3 &v) const;

    //STATICS
    //Devuelve la distancia entre v y u
    static float Distance(const Vector3 &v, const Vector3 &u);
    static Vector3 Lerp(const Vector3 &from, const Vector3 &to, float f);
};

#endif // VECTOR3_H
