#include "Vector2.h"

Vector2::Vector2()
{
    x = y = 0;
}

Vector2::Vector2(float x, float y)
{
    this->x = x;
    this->y = y;
}

Vector2::Vector2(int x, int y)
{
    this->x = (float)x;
    this->y = (float)y;
}

Vector2::Vector2(double x, double y)
{
    this->x = (float)x;
    this->y = (float)y;
}


float inline Vector2::Magnitude() const
{
    return sqrt(x*x + y*y);
}

Vector2 Vector2::Norm() const
{
    float mod = Magnitude();
    return Vector2(x/mod, y/mod);
}

float Vector2::Distance(const Vector2 &v, const Vector2 &u)
{
    return sqrt((v.x-u.x)*(v.x-u.x) + (v.y-u.y)*(v.y-u.y));
}


Vector2& Vector2::operator=(const Vector2 &v)
{
    this->x = v.x;
    this->y = v.y;
    return *this;
}

Vector2 Vector2::operator+(const Vector2 &v) const
{
    return Vector2(x + v.x, y + v.y);
}

Vector2 Vector2::operator-(const Vector2 &v) const
{
    return Vector2(x - v.x, y - v.y);
}

Vector2 Vector2::operator*(const float a) const
{
    return Vector2(x*a, y*a);
}

Vector2 Vector2::operator/(const float a) const
{
    return Vector2(x/a, y/a);
}


bool Vector2::operator==(const Vector2 &v) const
{
    return x == v.x and y == v.y;
}

Vector2 Vector2::Lerp(const Vector2 &from, const Vector2 &to, float f)
{
    return from + (to - from) * f;
}
