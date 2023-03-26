#include "DrawCommands.h"

GLuint DrawCommands::PositionVBO(const std::vector<GLfloat>& vertices, GLuint& program) {
    GLuint vertexBuffer;
    glGenBuffers(1, &vertexBuffer);
    Utilities::PrintErrors("After glGenBuffers");
    glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
    Utilities::PrintErrors("After glBindBuffer");
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(GLfloat), &vertices[0], GL_STATIC_DRAW);
    Utilities::PrintErrors("After glBufferData");
    auto loc = glGetAttribLocation(program, "position");
    Utilities::PrintErrors("After glGetAttribLocation");
    glVertexAttribPointer(loc, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), 0);
    Utilities::PrintErrors("After glVertexAttribPointer");
    glEnableVertexAttribArray(loc);
    Utilities::PrintErrors("After glEnableVertexAttribArray");
    
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
    glGenBuffers(1, &colorBuffer);
    Utilities::PrintErrors("After glGenBuffers");
    glBindBuffer(GL_ARRAY_BUFFER, colorBuffer);
    Utilities::PrintErrors("After glBindBuffer");
    glBufferData(GL_ARRAY_BUFFER, colors.size() * sizeof(GLfloat), &colors[0], GL_STATIC_DRAW);
    Utilities::PrintErrors("After glBufferData");
    auto loc = glGetAttribLocation(program, "color");
    Utilities::PrintErrors("After glGetAttribLocation");
    glVertexAttribPointer(loc, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(GLfloat), 0);
    Utilities::PrintErrors("After glVertexAttribPointer");
    glEnableVertexAttribArray(loc);
    Utilities::PrintErrors("After glEnableVertexAttribArray");
    
    return colorBuffer;
}


GLuint DrawCommands::IndexVBO(const std::vector<GLuint>& indices) {
    GLuint indexBuffer;
    glGenBuffers(1, &indexBuffer);
    Utilities::PrintErrors("After glGenBuffers");
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBuffer);
    Utilities::PrintErrors("After glBindBuffer");
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(GLuint), &indices[0], GL_STATIC_DRAW);
    Utilities::PrintErrors("After glBufferData");
    glDrawElements(GL_TRIANGLES, (GLsizei)indices.size(), GL_UNSIGNED_INT, 0);
    Utilities::PrintErrors("After glDrawElements");
    
    return indexBuffer;
}
