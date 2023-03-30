#version 300 es

precision highp float;

in vec4 vColor;
// ### receive additional vertex attribs
out vec4 Color;

// add uniforms from vertex shader or others (e.g., texture sampler)

void main()
{
    Color = vColor;
}

