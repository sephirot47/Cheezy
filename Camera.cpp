#include "Camera.h"
#include "Debug.h"

Camera::Camera()
{
    pos = Vector3(0.5, 0.5, 0.5);
    rot = Quaternion::Euler(0, 0, 0);
}

Vector3 Camera::GetForward()
{
    return rot.GetConjugate() * Vector3(0,0,-1);
}

Vector3 Camera::GetRight()
{
    return rot.GetConjugate() * Vector3(-1,0,0);
}

Vector3 Camera::GetUp()
{
    return rot.GetConjugate() * Vector3(0,-1,0);
}


void Camera::LookAt(Vector3 to)
{
    //rot = to - pos;
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
