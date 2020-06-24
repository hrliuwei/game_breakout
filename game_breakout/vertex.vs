#version 330 core
layout(location = 0) in vec4 vertex;

out vec2 Texcoords;

iniform mat4 model;
unifoem mat4 projection;

void main()
{
   Texcoords = vertex.zw;
   gl_Position = projection*model*vec4(vertex.xy, 0.0, 1.0);
}