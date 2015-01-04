#include "include/Camera.h"

Camera::Camera()
{
    pos = vec3(0.5, 0.5, 0.5);
    rot = quat(vec3(0, 0, 0));
}

void Camera::LookAt(vec3 camPos, vec3 lookTo, vec3 up)
{
    mat4 x = lookAt(camPos, lookTo, up);
    pos = camPos;
    rot = quat_cast(x);
}

void Camera::ApplyPerspective() const
{
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45, 1.0, 0.1, -5.0);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    float mat[16];
    mat4 x = mat4_cast(rot);
    const float *matPointer = (const float*)value_ptr(x);
    for(int i = 0; i < 16; ++i) mat[i] = matPointer[i];
    glMultMatrixf(mat);

    glTranslatef(-pos.x, -pos.y, -pos.z);
}

vec3 Camera::GetForward() const
{
    return conjugate(rot) * vec3(0, 0, -1);
}

vec3 Camera::GetUp() const
{
    return conjugate(rot) * vec3(0, 1, 0);
}

vec3 Camera::GetRight() const
{
    return conjugate(rot) * vec3(1, 0, 0);
}
