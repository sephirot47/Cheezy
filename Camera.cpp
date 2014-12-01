#include "Camera.h"
#include "Debug.h"

Camera::Camera()
{
    pos = Vector3(0.5, 0.5, 0.5);
    rot = Quaternion::Euler(0, 0, 0);
}

Vector3 Camera::GetForward()
{
    /*
    const float DEG2RAD = 3.141593f / 180;
    float sx, sy, sz, cx, cy, cz, theta;

    // rotation angle about X-axis (pitch)
    theta = rot.x * DEG2RAD;
    sx = sinf(theta);
    cx = cosf(theta);

    // rotation angle about Y-axis (yaw)
    theta = rot.y * DEG2RAD;
    sy = sinf(theta);
    cy = cosf(theta);

    // rotation angle about Z-axis (roll)
    theta = rot.z * DEG2RAD;
    sz = sinf(theta);
    cz = cosf(theta);

    // determine left axis
    //left.x = cy*cz;
    //left.y = sx*sy*cz + cx*sz;
    //left.z = -cx*sy*cz + sx*sz;

    // determine up axis
    //up.x = -cy*sz;
    //up.y = -sx*sy*sz + cx*cz;
    //up.z = cx*sy*sz + sx*cz;

    // determine forward axis
    Vector3 forward;
    forward.x = -sy;
    forward.y = -sx*cy;
    forward.z = cx*cy;

    return forward.Norm();
    */
    return Vector3(0,0,0);
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

    float mat[16];
    rot.GetRotMatrix(mat);
    glMultMatrixf(mat);

    glTranslatef(-pos.x, -pos.y, -pos.z);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    //DbgLog(rot);

    /*
    glRotatef(rot.x, 1.0, 0.0, 0.0);
    glRotatef(rot.y, 0.0, 1.0, 0.0);
    glRotatef(rot.z, 0.0, 0.0, 1.0);
    */
}
