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
    vec3 color = vec3(0.0f);
    vec3 sample[9];
    // 如果使用卷积矩阵，则对纹理的偏移像素进行采样
    if(chaos || shake)
        for(int i = 0; i < 9; i++)
            sample[i] = vec3(texture(scene, TexCoords.st + offsets[i]));

    // 处理特效
    if(chaos)
    {           
        for(int i = 0; i < 9; i++)
            color += vec3(sample[i] * edge_kernel[i]);
		FragColor = vec4(color,1.0f);
    }
    else if(confuse)
    {
        FragColor = vec4(1.0 - texture(scene, TexCoords).rgb, 1.0);
    }
    else if(shake)
    {
        for(int i = 0; i < 9; i++)
            color += vec3(sample[i] * blur_kernel[i]);
       FragColor = vec4(color,1.0f);
    }
    else
    {
        FragColor =  texture(scene, TexCoords);
    }
	
	
}
