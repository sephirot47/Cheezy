#include "Camera.h"

Camera::Camera()
{
    pos = Vector3(-0.5f, 3.0f, -0.5f);
    forward = Vector3(-0.5f, 3.0f, -0.5f);
}


void Camera::LookAt(Vector3 to)
{
    forward = to - pos;
}

void Camera::ApplyPerspective()
{
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45, 1.0, 0.1, -5.0);
    gluLookAt(pos.x, pos.y, pos.z,
              pos.x + forward.x, pos.y + forward.y, pos.z + forward.z,
              0.0, 1.0, 0.0);
}
