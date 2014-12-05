#ifndef MESH_H
#define MESH_H

#include <vector>
#include "Vector3.h"
#include "Vector2.h"

using namespace std;

class Mesh : public Component
{
private:
    int vertexBufferId;
    int vertexNumber;

public:

    Mesh();

    void Init(){}

    void Draw();
    void LoadFromFile(const char *filepath);
};

#endif // MESH_H
