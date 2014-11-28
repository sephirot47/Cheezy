#ifndef CAMERA_H
#define CAMERA_H

#include <GL/gl.h>
#include <GL/glu.h>
#include "Vector3.h"

class Camera
{
public:
    Vector3 pos;
    Vector3 rot;

    Camera();

    Vector3 GetForward();
    void LookAt(Vector3 to);
    void ApplyPerspective();
};

#endif // CAMERA_H
