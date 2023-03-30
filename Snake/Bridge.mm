#import "Bridge.h"

#import "GameManager.h"


@interface Bridge() {
    GLKView *glkView;
    std::chrono::time_point<std::chrono::steady_clock> lastTime;
    float elapsedFrames;
}

@end

@implementation Bridge

@synthesize Moving;
@synthesize Rotating;
@synthesize CameraZoom;
@synthesize CameraRotation;

- (void)dealloc
{
    
}

- (void)loadModels
{
    
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
    
    elapsedFrames = 0.0f;
    
    Camera::current = new Camera({ 0.0f, 0.0f, 10.0f }, { 0.0f, 0.0f, -10.0f }, (60.0f * M_PI) / 180.0f, 1.0f, 1.0f, 70.0f);
    
    GameManager::SceneSetup();
    
    Moving = false;
    Rotating = false;
    CameraZoom = 1.0f;
    CameraRotation = CGPointMake(0, 0);
    
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glEnable(GL_DEPTH_TEST);
    lastTime = std::chrono::steady_clock::now();
}

- (void)update
{
    // taking time
    auto currentTime = std::chrono::steady_clock::now();
    auto elapsedTime = std::chrono::duration_cast<std::chrono::milliseconds>(currentTime - lastTime).count();
    lastTime = currentTime;
    
    //projection matrix
    float aspectRatio = (float) glkView.drawableWidth / (float) glkView.drawableHeight;
    Camera::current->SetAspectRatio(aspectRatio);
    
    GameManager::UpdateGameObjects();
    
    if (elapsedFrames >= 30.0f)
    {
        [self fixedUpdate];
        elapsedFrames = 0.0f;
    }
    elapsedFrames += 1.0f;
    
}
- (void)fixedUpdate
{
    GameManager::FixedUpdateGameObjects();
}

- (void)draw:(CGRect)drawRect
{
    glViewport(0, 0, (int) glkView.drawableWidth, (int) glkView.drawableHeight);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    // draw vertices here
    GameManager::DrawGameObjects();
}

- (void)setDir:(int)dir {
    GameManager::SetDirection(dir, elapsedFrames);
}

- (int)getScore {
    return GameManager::score;
}

@end
