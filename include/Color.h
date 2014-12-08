#ifndef COLOR_H
#define COLOR_H

#include <iostream>
#include <string>
#include <stdio.h>
#include <cmath>


using namespace std;

class Color
{
public:

    float r, g, b, a;
    Color();
    Color(float r, float g, float b);
    Color(float r, float g, float b, float a);

    Color& operator=(const Color &v);
    Color  operator+(const Color &v) const;
    Color  operator-(const Color &v) const;
    Color  operator*(const float f)    const; //Multiplica r,g,b,a por un float f
    Color  operator/(const float f)    const; //Divide r,g,b,a entre un float f

    bool operator==(const Color &v) const;

    //STATICS
    ///\brief Returns the distance between color v and u (wtf?)
    static float Distance(const Color &v, const Color &u);

    ///\brief Returns de linear interpolation between from and to.
    static Color Lerp(const Color &from, const Color &to, float f);
};

#endif // COLOR_H
