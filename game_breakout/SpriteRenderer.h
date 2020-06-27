#pragma once
#include "shader.h"
class SpriteRenderer
{
public:
	SpriteRenderer(Shader shader);
	~SpriteRenderer();

	void DrawSprite(unsigned int texture, glm::vec2 positon,
		glm::vec2 size = glm::vec2(10, 10), GLfloat rotate = 0.0f,
		glm::vec3 color = glm::vec3(1.0f));

	void InitRenderData();

private:
	Shader m_shader;
	GLuint quadVAO;

	
};

