#pragma once
#include "shader.h"
class SpriteRenderer
{
public:
	SpriteRenderer(Shader &shader);
	~SpriteRenderer();

	void DrawSprite(unsigned int &texture, glm::vec2 positon,
		glm::vec2 size = glm::vec2(10, 10), GLfloat rorate = 0.0f,
		glm::vec3 color = glm::vec3(1.0f));

private:
	Shader shader;
	GLuint quadVAO;

	void InitRenderData();
};

