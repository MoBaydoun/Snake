#pragma once

#include "Includes.h"

class Renderer
{
public:
    Renderer(NSString *texName = @"white.jpg")
    {
        const char *vShaderPath = Utilities::FindPath("Advanced.vsh");
        const char *fShaderPath = Utilities::FindPath("Advanced.fsh");
        char *vShaderStr = Utilities::ReadShaderFile(vShaderPath);
        char *fShaderStr = Utilities::ReadShaderFile(fShaderPath);
        this->program = Utilities::LoadProgram(vShaderStr, fShaderStr);
        tex = Utilities::LoadTexture(texName);
    }
    
    void SetUniform(const std::string& uniformName)
    {
        auto location = glGetUniformLocation(program, uniformName.c_str());
        Utilities::PrintErrors("After glGetUniformLocation");
        locations.insert({ uniformName, location });
    }
    
    GLint& operator[](const char *str)
    {
        return locations.find(str)->second;
    }
    
    std::map<std::string, GLint> locations;
    GLuint program;
    GLuint tex;
};
