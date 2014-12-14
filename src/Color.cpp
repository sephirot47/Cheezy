#include "include/Color.h"

Color::Color()
{
    r = g = b = 0.5;
    a = 1;
}

Color::Color(float r, float g, float b)
{
    this->r = r;
    this->g = g;
    this->b = b;
    this->a = 1;
}

Color::Color(float r, float g, float b, float a)
{
    this->r = r;
    this->g = g;
    this->b = b;
    this->a = a;
}

Color& Color::operator=(const Color &v)
{
    this->r = v.r;
    this->g = v.g;
    this->b = v.b;
    this->a = v.a;
    return *this;
}

Color Color::operator+(const Color &v) const
{
    return Color(r + v.r, g + v.g, b + v.b, a + v.a);
}

Color Color::operator-(const Color &v) const
{
    return Color(r - v.r, g - v.g, b - v.b, a - v.a);
}

Color Color::operator*(const float f) const
{
    return Color(r*f, g*f, b*f, a*f);
}

Color Color::operator/(const float f) const
{
    return Color(r/f, g/f, b/f, a/f);
}

bool Color::operator==(const Color &v) const
{
    return r == v.r and g == v.g and b == v.b and a == v.a;
}


float Color::Distance(const Color &v, const Color &u)
{
    return sqrt((v.r-u.r)*(v.r-u.r) + (v.g-u.g)*(v.g-u.g) + (v.b-u.b)*(v.b-u.b));
}

Color Color::Lerp(const Color &from, const Color &to, float f)
{
    return from + (to - from) * f;
}
