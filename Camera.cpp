#include "Camera.h"

Camera::Camera()
{
    pos = Vector3(0, 0, 0);
    rot = Vector3(0, 0, 0);
}

Vector3 Camera::GetForward()
{
    return (rot).Norm();
}

void Camera::LookAt(Vector3 to)
{
    rot = to - pos;
}

void Camera::ApplyPerspective()
{
    glMatrixMode(GL_PROJECTION);
    glPushMatrix();
    glLoadIdentity();
    gluPerspective(45, 1.0, 0.1, -5.0);
    glTranslatef(pos.x, pos.y, pos.z);

    glRotatef(rot.x, 1.0, 0.0, 0.0);
    glRotatef(rot.y, 0.0, 1.0, 0.0);
    glRotatef(rot.z, 0.0, 0.0, 1.0);
    glPopMatrix();
}
