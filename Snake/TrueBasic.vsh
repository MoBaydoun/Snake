#version 300 es

layout(location = 0) in vec3 position;
layout(location = 1) in vec4 color;
// ### add any other vert attributes here
out vec4 v_color;
// ### add any other vert attributes to pass through here

uniform mat4 mvp;
// ### add any other uniforms (e.g., normal matrix) here

void main()
{
    // Simple passthrough shader
    v_color = color;
    gl_Position = mvp * vec4(position, 1.0);
}
