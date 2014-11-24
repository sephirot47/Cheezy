#ifndef COLOR_H
#define COLOR_H

#include <iostream>
#include <string>
#include <stdio.h>
#include <cmath>
#include "Printable.h"

using namespace std;

class Color : public Printable
{
public:

    float r, g, b, a;
    Color();
    Color(float r, float g, float b);
    Color(float r, float g, float b, float a);

    string ToString() const; //Devuelve el string "(r,g,b,a)"

    Color& operator=(const Color &v);
    Color  operator+(const Color &v) const;
    Color  operator-(const Color &v) const;
    Color  operator*(const float f)    const; //Multiplica r,g,b,a por un float f
    Color  operator/(const float f)    const; //Divide r,g,b,a entre un float f

    bool operator==(const Color &v) const;

    //STATICS
    //Devuelve la distancia entre v y u
    static float Distance(const Color &v, const Color &u);
    static Color Lerp(const Color &from, const Color &to, float f);
};

#endif // COLOR_H
