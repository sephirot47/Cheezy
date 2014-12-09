#include "Material.h"

Material::Material()
{
    vertexShader = fragmentShader = 0;
    vertexShaderId = fragmentShaderId = -1;
    programId = -1;
}

bool Material::AttachShader(Shader &shader)
{
    int shaderType = shader.GetType();
    switch(shaderType)
    {
        case CZ_VERTEX_SHADER:
            vertexShader = &shader;
            vertexShaderId = shader.GetShaderId();
            break;

        case CZ_FRAGMENT_SHADER:
            fragmentShader = &shader;
            fragmentShaderId = shader.GetShaderId();
            break;
    }

    //Create the shader program
    DBG_ASSERT_GL_RET(programId = glCreateProgram());

    //Attach the shaders to the program
    if(vertexShader != 0) glAttachShader(programId, vertexShaderId);
    if(fragmentShader != 0) glAttachShader(programId, fragmentShaderId);

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
    if(vertexShader != 0) glDetachShader(programId, vertexShaderId);
    if(fragmentShader != 0) glDetachShader(programId, fragmentShaderId);

    return true; //Everything went GOOD!
}

int Material::GetShaderId(unsigned int shaderType)
{
    switch(shaderType)
    {
        case CZ_VERTEX_SHADER:
            return vertexShaderId;

        case CZ_FRAGMENT_SHADER:
            return fragmentShaderId;
    }
    
    return -1;
}

void Material::UseProgram()
{
    if(programId > 0) glUseProgram(programId);
    else DbgWarning("No shaders attched to this material.");
}

void Material::UnUseProgram()
{
    glUseProgram(0);
}
