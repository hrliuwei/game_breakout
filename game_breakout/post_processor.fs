#version 330 core

in vec2 TexCoords;
out vec4 FragColor;

uniform sampler2D scene;
uniform vec2  offsets[9];
uniform int edge_kernel[9];
uniform float blur_kernel[9];

uniform bool chaos;
uniform bool confuse;
uniform bool shake;

void main()
{
    if(chaos){
	FragColor = vec4(1.0f,1.0f,1.0f,1.0f);
	}
	else
	{
	FragColor = texture(scene, TexCoords);
	}
	
	
	
}
