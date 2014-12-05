#include "Camera.h"

Camera::Camera()
{
    pos = Vector3(0.5, 0.5, 0.5);
    rot = Quaternion::Euler(0, 0, 0);
}

void Camera::LookAt(Vector3 to, Vector3 eye, Vector3 up)
{
    pos = eye;

    Vector3 forward = (to-eye).Norm();
    up = up.Norm();
    float cos_theta = Vector3::Dot(up, forward);
    float angle = acos(cos_theta);
    Vector3 w = Vector3::Cross(up, forward).Norm();
    rot = Quaternion::FromAxisAngle(angle, w);
}

void Camera::ApplyPerspective()
{
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45, 1.0, 0.1, -5.0);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    float mat[16];
    rot.GetRotMatrix(mat);
    glMultMatrixf(mat);

    glTranslatef(-pos.x, -pos.y, -pos.z);

    //DbgLog(rot);

    /*
    glRotatef(rot.x, 1.0, 0.0, 0.0);
    glRotatef(rot.y, 0.0, 1.0, 0.0);
    glRotatef(rot.z, 0.0, 0.0, 1.0);
    */
}
