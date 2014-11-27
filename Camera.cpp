#include "Camera.h"

Camera::Camera()
{
    pos = Vector3(0.5, 0.5, 0.5);
    rot = Vector3(0, 0, 0);
}

Vector3 Camera::GetForward()
{
    return (Vector3(-rot.z, -rot.x, -rot.y)).Norm();
}

void Camera::LookAt(Vector3 to)
{
    rot = to - pos;
}

void Camera::ApplyPerspective()
{
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45, 1.0, 0.1, -5.0);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glTranslatef(pos.x, pos.y, pos.z);

    glRotatef(rot.x, 1.0, 0.0, 0.0);
    glRotatef(rot.y, 0.0, 1.0, 0.0);
    glRotatef(rot.z, 0.0, 0.0, 1.0);
}
