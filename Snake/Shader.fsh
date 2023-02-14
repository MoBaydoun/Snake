#version 300 es

precision highp float;
in vec4 v_color;
// ### receive additional vertex attribs
out vec4 o_fragColor;

// add uniforms from vertex shader or others (e.g., texture sampler)

void main()
{
    o_fragColor = v_color;
}
