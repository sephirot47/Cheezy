#ifndef CAMERA_H
#define CAMERA_H

#include <GL/gl.h>
#include <GL/glu.h>
#include "Vector3.h"

class Camera
{
public:
    Vector3 pos;
    Vector3 forward;

    Camera();

    void ApplyPerspective();
    void LookAt(Vector3 to);
};

#endif // CAMERA_H
