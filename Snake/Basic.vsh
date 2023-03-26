#version 300 es

layout(location = 0) in vec4 position;
layout(location = 1) in vec4 color;
// ### add any other vert attributes here
out vec4 v_color;
// ### add any other vert attributes to pass through here

uniform mat4 mvp;
// ### add any other uniforms (e.g., normal matrix) here

void main()
{
    // Simple passthrough shader
    v_color = color * vec4(1.0f, 0.0f, 0.0f, 1.0f);
    gl_Position = mvp * position;
}

