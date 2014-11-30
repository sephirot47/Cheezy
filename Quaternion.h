#ifndef QUATERNION_H
#define QUATERNION_H

#include "Vector3.h"
#include <iostream>
#include <string>
#include <stdio.h>
#include <cmath>
#include "Printable.h"

using namespace std;

class Quaternion : public Printable
{
public:

    float x, y, z, w;

    Quaternion();
    Quaternion(float x, float y, float z, float w);
    Quaternion(Vector3 xyz, int w);
    Quaternion(Vector3 xyz, float w);
    Quaternion(Vector3 xyz, double w);


    string ToString() const; //Devuelve el string "(x,y,z)"

    Quaternion& operator=(const Vector3 &v);
    Quaternion  operator+(const Quaternion &v) const;
    Quaternion  operator-(const Quaternion &v) const;
    Quaternion  operator*(const float a)    const; //Multiplica x,y,z por un entero a
    Quaternion  operator/(const float a)    const; //Divide x,y,z entre un entero a

    Quaternion operator* (const Quaternion &q) const;
    Vector3 operator* (const Vector3 &vec);

    bool operator==(const Quaternion &v) const;


    void GetRotMatrix(float (&mat)[16]) const;
    Quaternion GetConjugate() const;

    //STATICS
    //Devuelve la distancia entre v y u
    static Quaternion Lerp(const Quaternion &from, const Quaternion &to, float f);
};

#endif	
