#pragma once

#include "Includes.h"

class DrawCommands {
public:
    static GLuint PositionVBO(const std::vector<GLfloat>& vertices, GLuint& program);
    static GLuint NormalVBO(const std::vector<GLfloat>& normals, GLuint& program);
    static GLuint TexCoordVBO(const std::vector<GLfloat>& texCoords, GLuint& program);
    static GLuint ColorVBO(const std::vector<GLfloat>& colors, GLuint& program);
    static GLuint IndexVBO(const std::vector<GLuint>& indices);
    private:
    DrawCommands() {}
};
