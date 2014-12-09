#include "FileReader.h"

bool FileReader::ReadOBJ(const char *filepath, vector<Vertex> &vertices)
{
    vector<Vector3> vertexPos;
    vector<Vector2> vertexUv;
    vector<unsigned int> vertexPosIndexes, vertexUvIndexes;

    ifstream f(filepath, ios::in);
    DBG_ASSERT_RET_MSG(f.is_open(), "Error opening the mesh file");
    string line;
    while(getline(f, line))
    {
        stringstream ss(line);
        string lineHeader;
        if(!(ss >> lineHeader)) continue;
        if(lineHeader == "v")
        {
            Vector3 pos;
            DBG_ASSERT_RET_MSG(ss >> pos.x, "Error reading the mesh file");
            DBG_ASSERT_RET_MSG(ss >> pos.y, "Error reading the mesh file");
            DBG_ASSERT_RET_MSG(ss >> pos.z, "Error reading the mesh file");
            vertexPos.push_back(pos);
        }
        else if(lineHeader == "vt") //Cargamos uvs, suponemos que antes ya se han leido las x,y,z de los vertices
        {
            Vector2 uv;
            DBG_ASSERT_RET_MSG(ss >> uv.x, "Error reading the mesh file");
            DBG_ASSERT_RET_MSG(ss >> uv.y, "Error reading the mesh file");
            vertexUv.push_back(uv);
        }
        else if(lineHeader == "f")
        {
            unsigned int vertexPosIndex[3], vertexUvIndex[3], foo;
            char c;

            DBG_ASSERT_RET_MSG(ss >> vertexPosIndex[0], "Error reading the mesh file");
            DBG_ASSERT_RET_MSG(ss >> c, "Error reading the mesh file");  //Read the '/'
            DBG_ASSERT_RET_MSG(ss >> vertexUvIndex[0], "Error reading the mesh file");
            DBG_ASSERT_RET_MSG(ss >> c, "Error reading the mesh file");
            DBG_ASSERT_RET_MSG(ss >> foo, "Error reading the mesh file");

            DBG_ASSERT_RET_MSG(ss >> vertexPosIndex[1], "Error reading the mesh file");
            DBG_ASSERT_RET_MSG(ss >> c, "Error reading the mesh file");
            DBG_ASSERT_RET_MSG(ss >> vertexUvIndex[1], "Error reading the mesh file");
            DBG_ASSERT_RET_MSG(ss >> c, "Error reading the mesh file");
            DBG_ASSERT_RET_MSG(ss >> foo, "Error reading the mesh file");

            DBG_ASSERT_RET_MSG(ss >> vertexPosIndex[2], "Error reading the mesh file");
            DBG_ASSERT_RET_MSG(ss >> c, "Error reading the mesh file");
            DBG_ASSERT_RET_MSG(ss >> vertexUvIndex[2], "Error reading the mesh file");
            DBG_ASSERT_RET_MSG(ss >> c, "Error reading the mesh file");
            DBG_ASSERT_RET_MSG(ss >> foo, "Error reading the mesh file");

            vertexPosIndexes.push_back(vertexPosIndex[0]);
            vertexPosIndexes.push_back(vertexPosIndex[1]);
            vertexPosIndexes.push_back(vertexPosIndex[2]);
            vertexUvIndexes.push_back(vertexUvIndex[0]);
            vertexUvIndexes.push_back(vertexUvIndex[1]);
            vertexUvIndexes.push_back(vertexUvIndex[2]);
        }
    }

    for(int i = 0; i < (int)vertexPosIndexes.size(); ++i)
    {
        Vertex v;
        v.pos = vertexPos[ vertexPosIndexes[i] - 1 ];
        v.uv  =  vertexUv[ vertexUvIndexes [i] - 1 ];
        vertices.push_back(v);
    }

    return true;
}
