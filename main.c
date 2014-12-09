#include <stdio.h>
#include <iostream>

using namespace std;

int main()
{
    bool uvs, normals, triangles;
    FILE *f;
    f = fopen("file", "r");
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
                uvs = (fgetc(f) != '/');
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
                while((c = fgetc(f)) != '\n')
                {
                    if(lastChar == ' ' && c != ' ') ++n;
                    lastChar = c;
                }
                triangles = (n == 3);
            }
            break; //return;
        }

        fseek(f, -3, SEEK_CUR);
    }
    cout << (uvs ? "uvs ":"") << (normals ? "normals ":"") << (triangles ? "tris" : "quads") << endl;
    return 0;
}
