#include "include/FileReader.h"

FileReaderFormat FileReader::GetFormat(const char *filepath)
{
    unsigned int i = 0;
    while(filepath[i] != '.') ++i;
    ++i;
    if(i < strlen(filepath) && strcmp(&filepath[i], "obj") == 0) return FormatObj;
    return FormatUnknown;
}

bool FileReader::ReadMeshFile(const char *filepath, VertexGroup &vg, const VertexFormat &vf, bool &triangles)
{
    FileReaderFormat format = GetFormat(filepath);
    if(format == FormatUnknown){ DbgError("Unknown mesh format. Not loading mesh(" << filepath << ")"); return false;}

    if(format == FormatObj) return FileReader::ReadOBJ(filepath, vg, vf, triangles);

    return false;
}

void FileReader::GetOBJFormat(const char *filepath, bool &uvs, bool &normals, bool &triangles)
{
    FILE *f;
    f = fopen(filepath, "r");
    if(!f)
    {
        DbgError("Error trying to open '" << filepath << "'");
        return;
    }

    fseek(f, -3, SEEK_END);
    int n = 1;

    char c, lastChar;
    while(ftell(f) > 0)
    {
        lastChar = fgetc(f);
        c = fgetc(f);
        if((lastChar == '\n' || lastChar == '\r') && c == 'f')
        {
            int foo;
            while(fgetc(f) == ' '); //Leemos espacios despues de 'f'
            fseek(f, -1, SEEK_CUR);
            foo = fscanf(f, "%d", &foo); //Leemos primer indice
            if(fgetc(f) == ' ') uvs = normals = false; //Solo un indice, sin barras
            else //Hay algo tal que asi:  5/*
            {
                uvs = (fgetc(f) != '/');
                if(!uvs) normals = true; //Es tal que asi 5//8
                if(uvs) //Es algo tal que asi 5/8*
                {
                    fseek(f, -1, SEEK_CUR);
                    foo = fscanf(f, "%d", &foo); //Leemos segundo indice
                    if(fgetc(f) == '/') //Es algo tal que asi 5/8/11
                    {
                        fseek(f, -1, SEEK_CUR);
                        foo = fscanf(f, "%d", &foo); //Leemos ultimo indice
                        normals = true;
                    }
                    else  normals = false;
                }
            }

            //Son triangulos o quads?
            lastChar = c;
            while(!feof(f) && (c = fgetc(f)) != '\n')
            {
                if(lastChar == ' ' && c != ' ') ++n;
                lastChar = c;
            }
            triangles = (n <= 3);
            break;
        }
        fseek(f, -3, SEEK_CUR);
    }
    fclose(f);
}

bool FileReader::ReadOBJ(const char *filepath, VertexGroup &vg, const VertexFormat &vf, bool &triangles)
{
    vector<vec3> vertexPos, vertexNormals;
    vector<vec2> vertexUv;
    vector<unsigned int> vertexPosIndexes, vertexUvIndexes, vertexNormIndexes;
    bool hasUvs, hasNormals;

    FileReader::GetOBJFormat(filepath, hasUvs, hasNormals, triangles);

    ifstream f(filepath, ios::in);
    DBG_ASSERT_RET_MSG(f.is_open(), "Error opening the mesh file");
    string line;
    string errormsg = "Error reading the mesh file";
    while(getline(f, line))
    {
        stringstream ss(line);
        string lineHeader;
        if(!(ss >> lineHeader)) continue;
        if(lineHeader == "v")
        {
            vec3 pos;
            DBG_ASSERT_RET_MSG(ss >> pos.x, errormsg);
            DBG_ASSERT_RET_MSG(ss >> pos.y, errormsg);
            DBG_ASSERT_RET_MSG(ss >> pos.z, errormsg);
            vertexPos.push_back(pos);
        }
        else if(hasUvs && lineHeader == "vt") //Cargamos uvs
        {
            vec2 uv;
            DBG_ASSERT_RET_MSG(ss >> uv.x, errormsg);
            DBG_ASSERT_RET_MSG(ss >> uv.y, errormsg);
            vertexUv.push_back(uv);
        }
        else if(hasNormals && lineHeader == "vn") //Cargamos normals
        {
            vec3 normal;
            DBG_ASSERT_RET_MSG(ss >> normal.x, errormsg);
            DBG_ASSERT_RET_MSG(ss >> normal.y, errormsg);
            DBG_ASSERT_RET_MSG(ss >> normal.z, errormsg);
            vertexNormals.push_back(normal);
        }
        else if(lineHeader == "f")
        {
            int n = triangles ? 3 : 4;
            unsigned int index;
            char c;

            for (int i = 0; i < n; ++i)
            {
                DBG_ASSERT_RET_MSG(ss >> index, errormsg);
                vertexPosIndexes.push_back(index);
                
                if(hasUvs) 
                {
                    DBG_ASSERT_RET_MSG(ss >> c, errormsg);  //Read the '/'
                    DBG_ASSERT_RET_MSG(ss >> index, errormsg);
                    vertexUvIndexes.push_back(index);
                    
                    if (hasNormals)
                    {
                        DBG_ASSERT_RET_MSG(ss >> c, errormsg);
                        DBG_ASSERT_RET_MSG(ss >> index, errormsg);
                        vertexNormIndexes.push_back(index);
                    }
                } 
                else 
                {
                    if (hasNormals)
                    {
                        DBG_ASSERT_RET_MSG(ss >> c, errormsg);
                        DBG_ASSERT_RET_MSG(ss >> index, errormsg);
                        vertexNormIndexes.push_back(index);
                    }
                }
            }
        }
    }

    vg.Init(int(vertexPosIndexes.size()), vf); //Creamos el vertexGroup con el vertexCount y el vertexFormat adecuados
    float defaultUvs[2] = {0.5f, 0.5f};
    float defaultNormals[3] = {0.0f, 0.0f, 1.0f};
    for(int i = 0; i < vg.GetVertexCount(); ++i)
    {
        string posName = vf.GetPositionAttribute().GetName();
        string uvsName = vf.GetTexCoordsAttribute().GetName();
        string normalsName = vf.GetNormalsAttribute().GetName();

        vg.SetAttribute(posName, &vertexPos[vertexPosIndexes[i]-1], i);

        if(hasUvs)
            vg.SetAttribute(uvsName, &vertexUv[vertexUvIndexes[i]-1], i);
        else
            vg.SetAttribute(uvsName, &defaultUvs, i);

        if(hasNormals)
            vg.SetAttribute(normalsName, &vertexNormals[vertexNormIndexes[i]-1], i);
        else
            vg.SetAttribute(normalsName, &defaultNormals, i);
    }
    return true;
}

bool FileReader::ReadTexture(const char * filepath, vector<vec4> &pixels)
{
    return true;
}

bool FileReader::LoadBitmap(const char* filepath, vector<vec4> &pixels)
{
    return true;
}
