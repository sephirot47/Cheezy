#include "Mesh.h"

Mesh::Mesh()
{
    vertexCount = 0;
    type = "Mesh";
    glGenBuffers(1, &vertexBufferId);

    material = new Material();

    Shader *vertexShader = new Shader(CZ_VERTEX_SHADER, "Shaders/vertexShader.glsl");
    Shader *fragmentShader = new Shader(CZ_FRAGMENT_SHADER, "Shaders/fragmentShader.glsl");

    material->AttachShader(*vertexShader);
    material->AttachShader(*fragmentShader);
}

void Mesh::Draw()
{
    if(vertexCount <= 0) return;

    glBindBuffer(GL_ARRAY_BUFFER, vertexBufferId);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vector3), 0);

    material->UseProgram(); //Use the shader
    glDrawArrays(GL_TRIANGLES, 0, vertexCount);
    material->UnUseProgram(); //Dont use this shader from now on

    glDisableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void Mesh::LoadFromFile(const char *filepath)
{
    vector<Vector3> vertices, tempVertices;
    vector<unsigned int> vertexIndexes;

    FILE * f = fopen(filepath, "r");
    if(f == NULL)
    {
        DbgError("Error opening the Mesh file!");
        return;
    }

    while(!feof(f))
    {
        char lineHeader[1024];
        int res = fscanf(f, "%s", lineHeader);
        if(res < 0) break;
        if (strcmp(lineHeader, "v") == 0)
        {
            Vector3 v;
            res = fscanf(f, "%f %f %f\n", &v.x, &v.y, &v.z);
            if(res < 0) break;
            tempVertices.push_back(v);
        }
        else if (strcmp(lineHeader, "f") == 0)
        {
            unsigned int vertexIndex[3], foo;
            int matches = fscanf(f, "%d/%d/%d %d/%d/%d %d/%d/%d\n", &vertexIndex[0], &foo, &foo,
                                                                    &vertexIndex[1], &foo, &foo,
                                                                    &vertexIndex[2], &foo, &foo);

            if (matches != 9)
            {
                DbgError("Error reading the file!");
                break;
            }

            vertexIndexes.push_back(vertexIndex[0]);
            vertexIndexes.push_back(vertexIndex[1]);
            vertexIndexes.push_back(vertexIndex[2]);
        }
    }

    for(int i = 0; i < (int)vertexIndexes.size(); ++i)
        vertices.push_back(tempVertices[vertexIndexes[i]-1]);

    vertexCount = vertices.size();
    glBindBuffer(GL_ARRAY_BUFFER, vertexBufferId);
    glBufferData(GL_ARRAY_BUFFER, vertexCount * sizeof(Vector3), &vertices[0], GL_STATIC_DRAW); //Load the mesh to the GPU
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

int Mesh::GetVertexCount()
{
    return vertexCount;
}

