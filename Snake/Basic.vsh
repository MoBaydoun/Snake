#version 300 es

layout(location = 0) in vec3 position;
layout(location = 1) in vec3 normal;
layout(location = 2) in vec2 texCoord;
layout(location = 3) in vec4 color;

uniform mat4 mvp;
uniform vec3 lightPosition;

//external
out vec3 Position;
out vec3 Normal;
out vec2 TexCoord;
out vec4 Color;

//local
out vec3 LightDirection;
out vec3 ViewDirection;

void main()
{
    Position = position;
    Normal = normalize(mat3(transpose(inverse(mvp))) * normal);
    TexCoord = texCoord;
    Color = color;
    
    vec4 pos = mvp * vec4(position, 1.0);
    vec3 vertexPos = vec3(pos) / pos.w;
    LightDirection = normalize(lightPosition - vertexPos);
    ViewDirection = normalize(-vertexPos);
    
    gl_Position = pos;
}

