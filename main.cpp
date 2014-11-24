#include <iostream>
#include "Debug.h"
#include "Color.h"
#include "Vector2.h"
#include "Vector3.h"

using namespace std;

int main()
{
    Vector3 v, u, w;
    v = Vector3(1, 1, 1);
    u = Vector3(2, 2, 2);
    w = Vector3(3, 3, 3);
    Vector2 t(1, 0.5);
    Color c = Color(4, 5, 6, 1);
    Debug::Log(3 & v & "asd" & 6 & "sad" & 6 & w & 7.0f);
}
