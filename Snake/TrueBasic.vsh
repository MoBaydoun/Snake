#version 300 es

layout(location = 0) in vec3 position;
layout(location = 1) in vec4 color;

out vec4 vColor;

uniform mat4 mvp;
// ### add any other uniforms (e.g., normal matrix) here

void main()
{
    // Simple passthrough shader
    vColor = color;
    gl_Position = mvp * vec4(position, 1.0);
}
