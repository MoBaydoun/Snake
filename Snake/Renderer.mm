#import "Renderer.h"

#import "Utilities.h"

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
    
}

- (void)draw:(CGRect)drawRect
{
    // setting up viewport and clearing previous drawing
    glUniformMatrix4fv(uniforms[UNIFORM_MODELVIEWPROJECTION_MATRIX], 1, FALSE, (const float *) mvp.m);
    glViewport(0, 0, (int) glkView.drawableWidth, (int) glkView.drawableHeight);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glUseProgram(program);
    
    // draw vertices here
}

@end
