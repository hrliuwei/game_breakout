#version 330 core
in vec2 TexCoords;

out vec4 Fragcolor;
in vec4 ParticleColor;

uniform sampler2D sprite;


void main()
{
    Fragcolor =  vec4(0.5f,0.5f,0.5f,1.0f);
}