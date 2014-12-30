#include "include/Material.h"

Material::Material()
{
    vertexShader = fragmentShader = 0;
    texture = 0;

    programId = -1;
}

Material::~Material()
{
    if(vertexShader) delete vertexShader;
    if(fragmentShader) delete fragmentShader;
    if(texture) delete texture;
}

bool Material::AttachShader(Shader &shader)
{
    int shaderType = shader.GetType();
    switch(shaderType)
    {
        case CZ_VERTEX_SHADER:
            vertexShader = &shader;
            break;

        case CZ_FRAGMENT_SHADER:
            fragmentShader = &shader;
            break;
    }

    //Create the shader program
    DBG_ASSERT_GL_RET(programId = glCreateProgram());

    //Attach the shaders to the program
    if(vertexShader)   glAttachShader(programId, vertexShader->GetId());
    if(fragmentShader) glAttachShader(programId, fragmentShader->GetId());

    //Link it!
    DBG_ASSERT_GL_RET(glLinkProgram(programId));

    int isLinked;
    glGetProgramiv(programId, GL_LINK_STATUS, &isLinked);
    if(isLinked == GL_FALSE)
    {
        DbgError("There was an error when trying to link your shaders: ");

        char errorInfo[CZ_MAX_MATERIAL_ERROR_LOG_SIZE];
        glGetProgramInfoLog(programId, CZ_MAX_MATERIAL_ERROR_LOG_SIZE, 0, errorInfo);

        DbgLog(errorInfo);

        //Undo the changes
        glDeleteProgram(programId);
        return false;
    }

    //Detach the shaders(we dont need them attached anymore)
    if(vertexShader)   glDetachShader(programId, vertexShader->GetId());
    if(fragmentShader) glDetachShader(programId, fragmentShader->GetId());

    return true; //Everything went GOOD!
}

int Material::GetShaderId(unsigned int shaderType)
{
    switch(shaderType)
    {
        case CZ_VERTEX_SHADER: return vertexShader ? vertexShader->GetId() : -1;
        case CZ_FRAGMENT_SHADER: return fragmentShader ? fragmentShader->GetId() : -1;
    }
    return -1;
}

int Material::GetProgramId()
{
    return programId;
}

void Material::SetTexture(Texture *t)
{
    texture = t;
}

void Material::SetUniform(string name, vec4 value)
{
    if(programId < 0) { DbgWarning("The material program is not linked, can't set any uniform."); return; }
    int location = glGetUniformLocation(programId, name.c_str());
    if(location < 0){ DbgWarning("The uniform '" << name << "' couldn't be found."); return; }
    glUniform4f(location, value.x, value.y, value.z, value.w);
}

void Material::SetUniform(string name, vec3 value)
{
    if(programId < 0) { DbgWarning("The material program is not linked, can't set any uniform."); return; }
    int location = glGetUniformLocation(programId, name.c_str());
    if(location < 0){ DbgWarning("The uniform '" << name << "' couldn't be found."); return; }
    glUniform3f(location, value.x, value.y, value.z);
}

void Material::SetUniform(string name, vec2 value)
{
    if(programId < 0) { DbgWarning("The material program is not linked, can't set any uniform."); return; }
    int location = glGetUniformLocation(programId, name.c_str());
    if(location < 0){ DbgWarning("The uniform '" << name << "' couldn't be found."); return; }
    glUniform2f(location, value.x, value.y);
}

void Material::SetUniform(string name, float value)
{
    if(programId < 0) { DbgWarning("The material program is not linked, can't set any uniform."); return; }
    int location = glGetUniformLocation(programId, name.c_str());
    if(location < 0){ DbgWarning("The uniform '" << name << "' couldn't be found."); return; }
    glUniform1f(location, value);
}

void Material::SetUniform(string name, int value)
{
    if(programId < 0) { DbgWarning("The material program is not linked, can't set any uniform."); return; }
    int location = glGetUniformLocation(programId, name.c_str());
    if(location < 0){ DbgWarning("The uniform '" << name << "' couldn't be found."); return; }
    glUniform1i(location, value);
}

void Material::Bind()
{
    if(programId > 0) glUseProgram(programId);
    if(texture) texture->Bind();
}

void Material::UnBind()
{
    if(programId > 0) glUseProgram(0);
    if(texture) texture->UnBind();
}

