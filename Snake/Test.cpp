#include "Test.h"

Test::Test(vec3f position) : Entity() {
    Create(position);
}

void Test::Create(vec3f position) {
    GLfloat testVerts[] =
    {
        -0.25f + position.x, 0.5f + position.y, -5.0f + position.z,
        0.125f + position.x, 0.5f + position.y, -5.0f + position.z,
        0.125f + position.x, -0.5f + position.y, -5.0f + position.z,
        -0.25f + position.x, -0.5f + position.y, -5.0f + position.z
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

/** Function should be made in order to increase the size of the snake once the snake gets the pills. */
void Increase_Snake_Size(){
    std::cout << "Snake Will Grow" << std::endl;
}
