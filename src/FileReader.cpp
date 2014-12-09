#include "FileReader.h"

int FileReader::GetFormat(const char *filepath)
{
    char *format = filepath;
    while(*format != '.') ++format;
    ++format;
    if(strcmp(format, "obj") == 0) return CZ_FORMAT_OBJ;
    return CZ_FORMAT_UNKNOWN;
}

bool FileReader::ReadMeshFile(const char *filepath, vector<Vertex> &vertices)
{
    int format = GetFormat(filepath);
    if(format == CZ_FORMAT_UNKNOWN){ DbgError("Unknown mesh format. Not loading mesh(" << filepath << ")"); return false;}

    if(format == CZ_FORMAT_OBJ) return FileReader::ReadOBJ(filepath, vertices);

    return false;
}

void FileReader::GetOBJFormat(const char *filepath, bool &uvs, bool &normals, bool &triangles)
{
    FILE *f;
    f = fopen(filepath, "r");
    fseek(f, -3, SEEK_END);

    char c, lastChar;
    while(ftell(f) > 0)
    {
        lastChar = fgetc(f);
        c = fgetc(f);
        if(lastChar == '\n' && c == 'f')
        {
            int foo;
            while((c = fgetc(f)) == ' '); //Leemos espacios despues de 'f'
            fscanf(f, "%d", &foo); //Leemos primer indice
            if((c = fgetc(f)) == ' ') //Solo un indice, sin barras
            {
                uvs = normals = false;
            }
            else //Hay algo tal que asi:  5/*
            {
                uvs = (fgetc(c) != '/');
                if(!uvs) normals = true; //Es tal que asi 5//8

                if(uvs) //Es algo tal que asi 5/8*
                {
                    fscanf(f, "%d", &foo); //Leemos segundo indice
                    if(fgetc(f) == '/') //Es algo tal que asi 5/8/11
                    {
                        fscanf(f, "%d", &foo); //Leemos ultimo indice
                        normals = true;
                    }
                    else normals = false;
                }

                //Son triangulos o quads?
                int n = 1;
                lastChar = c;
                while((c = fgetc(c)) != '\n')
                {
                    if(lastChar == ' ' && c != ' ') ++n;
                    lastChar = c;
                }
                triangles = (n == 3);
            }
            return;
        }

        fseek(f, -3, SEEK_CUR);
    }
}

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
