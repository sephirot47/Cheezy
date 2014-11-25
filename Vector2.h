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

    Vector2 Norm();   //Devuelve el vector normalizado

    float Mod(); //Devuelve el modulo del vector

    string ToString() const; //Devuelve el string "(x,y)"

    Vector2& operator=(const Vector2 &v);
    Vector2  operator+(const Vector2 &v) const;
    Vector2  operator-(const Vector2 &v) const;
    Vector2  operator*(const float a) const; //Multiplica x,y por un entero a
    Vector2  operator/(const float a) const; //Divide x,y entre un entero a

    bool operator==(const Vector2 &v) const;

    //Devuelve la distancia entre v y u
    static float Distance(const Vector2 &v, const Vector2 &u);
    Vector2 Lerp(const Vector2 &from, const Vector2 &to, float f);
};

#endif // Vector2_H
