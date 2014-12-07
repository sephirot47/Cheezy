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
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);

    material->UseProgram();
    glDrawArrays(GL_TRIANGLES, 0, vertexCount);
    material->UnUseProgram();

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
            unsigned int vertexIndex[3], uvIndex[3], normalIndex[3];
            int matches = fscanf(f, "%d/%d/%d %d/%d/%d %d/%d/%d\n", &vertexIndex[0], &uvIndex[0], &normalIndex[0],
                                                                    &vertexIndex[1], &uvIndex[1], &normalIndex[1],
                                                                    &vertexIndex[2], &uvIndex[2], &normalIndex[2]);
                                                                    //&vertexIndex[3], &uvIndex[3], &normalIndex[3] );
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
    glBufferData(GL_ARRAY_BUFFER, vertices.size(), &vertices[0], GL_STATIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

int Mesh::GetVertexCount()
{
    return vertexCount;
}

