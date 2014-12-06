#include "Material.h"

Material::Material()
{
    shader = 0;
}

void Material::SetShader(Shader &shader)
{
    shader = &shader;
}


int Material::GetShaderId()
{
    if(shader == 0) return -1;
    return shader->GetShaderId();
}
