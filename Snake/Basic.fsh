#version 300 es

precision mediump float;

uniform vec3 lightColor;
uniform vec3 objectColor;
uniform float shininess;
uniform sampler2D tex;

in vec3 Position;
in vec3 Normal;
in vec2 TexCoord;
in vec4 Color;

in vec3 LightDirection;
in vec3 ViewDirection;

out vec4 FragmentColor;

void main()
{
    vec3 ambient = 0.2 * lightColor;
    vec3 diffuse = max(dot(Normal, LightDirection), 0.0) * lightColor;
    vec3 specular = vec3(0.0);
    
    if (dot(Normal, LightDirection) > 0.0)
    {
        vec3 halfwayDir = normalize(LightDirection + ViewDirection);
        float spec = pow(max(dot(Normal, halfwayDir), 0.0), shininess);
        specular = spec * lightColor;
    }
    
    vec4 texColor = texture(tex, TexCoord);
    FragmentColor = vec4((ambient + diffuse + specular) * objectColor * texColor.rgb, texColor.a);
}

