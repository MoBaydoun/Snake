#version 300 es
precision mediump float;

in vec3 vertexNormal;
in vec2 vertexTexCoord;

uniform sampler2D tex;

out vec4 Color;

void main()
{
    vec4 color = texture(tex, vertexTexCoord);
    Color = color;
}
