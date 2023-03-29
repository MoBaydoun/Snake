#include "Utilities.h"

char *Utilities::ReadShaderFile(const char *fileName) {
    FILE *fp = fopen(fileName, "rb");
    if (fp == NULL)
        return NULL;
    
    fseek(fp , 0 , SEEK_END);
    long totalBytes = ftell(fp);
    fclose(fp);
    
    char *buf = (char *)malloc(totalBytes+1);
    memset(buf, 0, totalBytes+1);
    
    fp = fopen(fileName, "rb");
    if (fp == NULL)
        return NULL;
    
    size_t bytesRead = fread(buf, totalBytes, 1, fp);
    fclose(fp);
    if (bytesRead < 1)
        return NULL;

    return buf;
}

GLuint Utilities::LoadShader(GLenum type, const char *shaderSrc)
{
    GLuint shader = glCreateShader(type);
    Utilities::PrintErrors("After glCreateShader");
    if (shader == 0)
        return 0;
    
    glShaderSource(shader, 1, &shaderSrc, NULL);
    Utilities::PrintErrors("After glShaderSource");
    glCompileShader(shader);
    Utilities::PrintErrors("After glCompileShader");

    GLint compiled;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &compiled);
    Utilities::PrintErrors("After glGetShaderiv");
    if (!compiled)
    {
        GLint infoLen = 0;
        glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &infoLen);
        Utilities::PrintErrors("After glGetShaderiv");
        if (infoLen > 1)
        {
            char *infoLog = (char *)malloc(sizeof ( char ) * infoLen);
            glGetShaderInfoLog(shader, infoLen, NULL, infoLog);
            Utilities::PrintErrors("After glGetShaderInfoLog");
            std::cerr << "*** SHADER COMPILE ERROR:" << std::endl;
            std::cerr << infoLog << std::endl;
            free(infoLog);
        }
        glDeleteShader ( shader );
        Utilities::PrintErrors("After glDeleteShader");
        return 0;
    }
    
    return shader;
}

GLuint Utilities::LoadProgram(const char *vertShaderSrc, const char *fragShaderSrc)
{
    GLuint vertexShader = LoadShader(GL_VERTEX_SHADER, vertShaderSrc);
    if (vertexShader == 0)
        return 0;
    
    GLuint fragmentShader = LoadShader(GL_FRAGMENT_SHADER, fragShaderSrc);
    if (fragmentShader == 0)
    {
        glDeleteShader(vertexShader);
        Utilities::PrintErrors("After glDeleteShader");
        return 0;
    }
    
    static GLuint programObject = glCreateProgram();
    Utilities::PrintErrors("After glCreateProgram");
    if (programObject == 0)
    {
        glDeleteShader(vertexShader);
        Utilities::PrintErrors("After glDeleteShader");
        glDeleteShader(fragmentShader);
        Utilities::PrintErrors("After glDeleteShader");
        return 0;
    }
    
    glAttachShader(programObject, vertexShader);
    Utilities::PrintErrors("After glAttachShader");
    glAttachShader(programObject, fragmentShader);
    Utilities::PrintErrors("After glAttachShader");
    glLinkProgram(programObject);
    Utilities::PrintErrors("After glLinkProgram");
    
    GLint linked;
    glGetProgramiv(programObject, GL_LINK_STATUS, &linked);
    Utilities::PrintErrors("After glGetProgramiv");
    if (!linked)
    {
        GLint infoLen = 0;
        glGetProgramiv(programObject, GL_INFO_LOG_LENGTH, &infoLen);
        Utilities::PrintErrors("After glGetProgramiv");
        if (infoLen > 1)
        {
            char *infoLog = (char *)malloc(sizeof(char) * infoLen);
            glGetProgramInfoLog(programObject, infoLen, NULL, infoLog);
            Utilities::PrintErrors("After glGetProgramInfoLog");
            std::cerr << "*** SHADER LINK ERROR:" << std::endl;
            std::cerr << infoLog << std::endl;
            free(infoLog);
        }
        glDeleteProgram(programObject);
        Utilities::PrintErrors("After glDeleteProgram");
        return 0;
    }
    
    glDeleteShader(vertexShader);
    Utilities::PrintErrors("After glDeleteShader");
    glDeleteShader(fragmentShader);
    Utilities::PrintErrors("After glDeleteShader");
    

    return programObject;
}

const char* Utilities::FindPath(const char *fileName) {
    const char* result = [[[NSBundle mainBundle] pathForResource:[[NSString stringWithUTF8String:fileName] stringByDeletingPathExtension] ofType:[[NSString stringWithUTF8String:fileName] pathExtension]] cStringUsingEncoding:1];
    return result;
}

void Utilities::PrintErrors(const char *location)
{
    auto error = glGetError();
    switch (error) {
        case GL_NO_ERROR:
            break;
        case GL_INVALID_ENUM:
            std::cout << "Error: Invalid Enum" << '\n' << "Location: " << location << std::endl;
            break;
        case GL_INVALID_VALUE:
            std::cout << "Error: Invalid Value" << '\n' << "Location: " << location << std::endl;
            break;
        case GL_INVALID_OPERATION:
            std::cout << "Error: Invalid Operation" << '\n' << "Location: " << location << std::endl;
            break;
        case GL_OUT_OF_MEMORY:
            std::cout << "Error: Out of Memory" << '\n' << "Location: " << location << std::endl;
            break;
        default:
            std::cout << "Error: Unrecognized Error" << '\n' << "Location: " << location << std::endl;
            break;
    }
}

void Utilities::LoadTexture(NSString *fileName)
{
    CGImageRef spriteImage = [UIImage imageNamed:fileName].CGImage;
    if (!spriteImage) {
        NSLog(@"Failed to load image %@", fileName);
        exit(1);
    }
    
    size_t width = CGImageGetWidth(spriteImage);
    size_t height = CGImageGetHeight(spriteImage);
    
    GLubyte *spriteData = (GLubyte *) calloc(width*height*4, sizeof(GLubyte));
    
    CGContextRef spriteContext = CGBitmapContextCreate(spriteData, width, height, 8, width*4, CGImageGetColorSpace(spriteImage), kCGImageAlphaPremultipliedLast);
    
    CGContextDrawImage(spriteContext, CGRectMake(0, 0, width, height), spriteImage);
    
    CGContextRelease(spriteContext);
    
    GLuint texName;
    glGenTextures(1, &texName);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, texName);
    
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, (GLsizei) width, (GLsizei) height, 0, GL_RGBA, GL_UNSIGNED_BYTE, spriteData);
    
    free(spriteData);
}
