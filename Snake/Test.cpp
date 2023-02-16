#include "Test.h"

Test::Test(GLfloat xOffset) : Entity() {
    Create(xOffset);
}

void Test::Create(GLfloat xOffset) {
    GLfloat testVerts[] =
    {
        -0.25f + xOffset, 0.5f, -5.0f,
        0.125f + xOffset, 0.5f, -5.0f,
        0.125f + xOffset, -0.5f, -5.0f,
        -0.25f + xOffset, -0.5f, -5.0f
    };
    
    GLuint testIndices[] =
    {
        0, 1, 2,
        0, 2, 3
    };
    
    GLfloat testColors[] =
    {
        1.0f, 0.0f, 0.0f, 1.0f,
        1.0f, 0.0f, 0.0f, 1.0f,
        1.0f, 0.0f, 0.0f, 1.0f,
        1.0f, 0.0f, 0.0f, 1.0f
    };
    
    int numVertices = (int) (sizeof(testVerts) / sizeof(GLfloat));
    int numColors = (int) (sizeof(testColors) / sizeof(GLfloat));
    int numIndices = (int) (sizeof(testIndices) / sizeof(GLuint));
    
    vertices = (GLfloat *) malloc(sizeof(GLfloat) * numVertices);
    memcpy(vertices, testVerts, sizeof(testVerts));
    
    colors = (GLfloat *) malloc(sizeof(GLfloat) * numColors);
    memcpy(colors, testColors, sizeof(testColors));
    
    indices = (GLuint *) malloc(sizeof(GLuint) * numIndices);
    memcpy(indices, testIndices, sizeof(testIndices));
}

void Test::Update() {
    std::cout << "Update work??" << std::endl;
}
