#version 300 es

layout(location = 0) in vec3 position;
layout(location = 1) in vec3 normal;
layout(location = 2) in vec2 texCoord;

out vec3 vertexNormal;
out vec2 vertexTexCoord;

uniform mat4 mvp;
uniform mat3 nm;

void main()
{
    vertexNormal = normalize(nm * normal);
    vertexTexCoord = texCoord;
    gl_Position = mvp * vec4(position, 1.0);
}

