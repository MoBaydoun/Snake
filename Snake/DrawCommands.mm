#include "DrawCommands.h"

GLuint DrawCommands::PositionVBO(const std::vector<GLfloat>& vertices, GLuint& program) {
    GLuint vertexBuffer;
    glGenBuffers(1, &vertexBuffer);
    glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(GLfloat), &vertices[0], GL_STATIC_DRAW);
    auto loc = glGetAttribLocation(program, "position");
    glVertexAttribPointer(loc, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), 0);
    glEnableVertexAttribArray(loc);
    
    return vertexBuffer;
}

GLuint DrawCommands::NormalVBO(const std::vector<GLfloat>& normals, GLuint& program) {
    GLuint normalBuffer;
    glGenBuffers(1, &normalBuffer);
    glBindBuffer(GL_ARRAY_BUFFER, normalBuffer);
    glBufferData(GL_ARRAY_BUFFER, normals.size() * sizeof(GLfloat), &normals[0], GL_STATIC_DRAW);
    auto loc = glGetAttribLocation(program, "normal");
    glVertexAttribPointer(loc, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), 0);
    glEnableVertexAttribArray(loc);
    
    return normalBuffer;
}

GLuint DrawCommands::TexCoordVBO(const std::vector<GLfloat>& texCoords, GLuint& program) {
    GLuint texCoordBuffer;
    glGenBuffers(1, &texCoordBuffer);
    glBindBuffer(GL_ARRAY_BUFFER, texCoordBuffer);
    glBufferData(GL_ARRAY_BUFFER, texCoords.size() * sizeof(GLfloat), &texCoords[0], GL_STATIC_DRAW);
    auto loc = glGetAttribLocation(program, "texCoord");
    glVertexAttribPointer(loc, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(GLfloat), 0);
    glEnableVertexAttribArray(loc);
    
    return texCoordBuffer;
}

GLuint DrawCommands::ColorVBO(const std::vector<GLfloat>& colors, GLuint& program) {
    GLuint colorBuffer;
    Utilities::PrintErrors("Prior glGenBuffers Color");
    glGenBuffers(1, &colorBuffer);
    Utilities::PrintErrors("After glGenBuffers Color");
    glBindBuffer(GL_ARRAY_BUFFER, colorBuffer);
    glBufferData(GL_ARRAY_BUFFER, colors.size() * sizeof(GLfloat), &colors[0], GL_STATIC_DRAW);
    auto loc = glGetAttribLocation(program, "color");
    glVertexAttribPointer(loc, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(GLfloat), 0);
    glEnableVertexAttribArray(loc);
    
    return colorBuffer;
}


GLuint DrawCommands::IndexVBO(const std::vector<GLuint>& indices) {
    GLuint indexBuffer;
    glGenBuffers(1, &indexBuffer);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBuffer);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(GLuint), &indices[0], GL_STATIC_DRAW);
    
    return indexBuffer;
}
