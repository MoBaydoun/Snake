#import "Renderer.h"

#import "Entity.h"
#import "Test.h"

enum {
    UNIFORM_MODELVIEWPROJECTION_MATRIX,
    NUM_UNIFORMS
};

GLint uniforms[NUM_UNIFORMS];

enum {
    ATTRIB_VERTEX,
    NUM_ATTRIBUTES,
};

@interface Renderer() {
    GLKView *glkView;
    GLuint program;
    std::chrono::time_point<std::chrono::steady_clock> lastTime;
    GLKMatrix4 mvp;
}

@end

@implementation Renderer

- (void)dealloc
{
    glDeleteProgram(program);
}

- (void)loadModels
{
    Test *t = new Test({1.0f, 1.5f, 0.0f});
    Test *t1 = new Test({-1.0f, -1.5f, 0.0f});
}

- (bool)setupShaders
{
    char *vShaderStr = Utilities::ReadShaderFile([[[NSBundle mainBundle] pathForResource:[[NSString stringWithUTF8String:"Shader.vsh"] stringByDeletingPathExtension] ofType:[[NSString stringWithUTF8String:"Shader.vsh"] pathExtension]] cStringUsingEncoding:1]);
    char *fShaderStr = Utilities::ReadShaderFile([[[NSBundle mainBundle] pathForResource:[[NSString stringWithUTF8String:"Shader.fsh"] stringByDeletingPathExtension] ofType:[[NSString stringWithUTF8String:"Shader.fsh"] pathExtension]] cStringUsingEncoding:1]);
    program = Utilities::LoadProgram(vShaderStr, fShaderStr);
    if (program == 0)
        return false;
    
    uniforms[UNIFORM_MODELVIEWPROJECTION_MATRIX] = glGetUniformLocation(program, "modelViewProjectionMatrix");

    return true;
}

- (void)setup:(GLKView *)view
{
    view.context = [[EAGLContext alloc] initWithAPI:kEAGLRenderingAPIOpenGLES3];
    if (!view.context) {
        NSLog(@"Failed to create ES Context");
    }
    
    view.drawableDepthFormat = GLKViewDrawableDepthFormat24;
    glkView = view;
    [EAGLContext setCurrentContext:view.context];
    if (![self setupShaders]) return;
    
    glClearColor(0.0f, 1.0f, 1.0f, 0.2f);
    glEnable(GL_DEPTH_TEST);
    lastTime = std::chrono::steady_clock::now();
}

- (void)update
{
    // taking time
    auto currentTime = std::chrono::steady_clock::now();
    auto elapsedTime = std::chrono::duration_cast<std::chrono::milliseconds>(currentTime - lastTime).count();
    lastTime = currentTime;
    
    // set up camera
    mvp = GLKMatrix4Translate(GLKMatrix4Identity, 0.0f, 0.0f, -5.0f);
    float aspect = (float) glkView.drawableWidth / (float) glkView.drawableHeight;
    GLKMatrix4 perspective = GLKMatrix4MakePerspective(60.0f * M_PI / 180.0f, aspect, 1.0f, 20.0f);
    mvp = GLKMatrix4Multiply(perspective, mvp);
    
    // updates go here
    Entity::UpdateEntities();
}

- (void)draw:(CGRect)drawRect
{
    // setting up viewport and clearing previous drawing
    glUniformMatrix4fv(uniforms[UNIFORM_MODELVIEWPROJECTION_MATRIX], 1, FALSE, (const float *) mvp.m);
    glViewport(0, 0, (int) glkView.drawableWidth, (int) glkView.drawableHeight);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glUseProgram(program);
    // draw vertices here
    auto entities = Entity::GetEntities();
    for (auto &entity : entities)
    {
        GLuint vao;
        glGenVertexArrays(1, &vao);
        glBindVertexArray(vao);
        
        GLuint vertexBuffer, colorBuffer, indexBuffer;
        
        glGenBuffers(1, &vertexBuffer);
        glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
        glBufferData(GL_ARRAY_BUFFER, 12 * sizeof(GLfloat), entity->GetVertices(), GL_STATIC_DRAW);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), 0);
        glEnableVertexAttribArray(0);
        
        glGenBuffers(1, &colorBuffer);
        glBindBuffer(GL_ARRAY_BUFFER, colorBuffer);
        glBufferData(GL_ARRAY_BUFFER, 16 * sizeof(GLfloat), entity->GetColors(), GL_STATIC_DRAW);
        glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(GLfloat), 0);
        glEnableVertexAttribArray(1);
        
        glGenBuffers(1, &indexBuffer);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBuffer);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, 6 * sizeof(GLuint), entity->GetIndices(), GL_STATIC_DRAW);
        
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
        
        glDeleteBuffers(1, &vertexBuffer);
        glDeleteBuffers(1, &colorBuffer);
        glDeleteBuffers(1, &indexBuffer);
        glDeleteVertexArrays(1, &vao);
    }
}

@end
