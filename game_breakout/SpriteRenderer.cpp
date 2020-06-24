#include "SpriteRenderer.h"





void SpriteRenderer::InitRenderData()
{
	// ≈‰÷√ VAO/VBO
	GLuint VBO;
	GLfloat vertices[] = {
		// Œª÷√     // Œ∆¿Ì
		0.0f, 1.0f, 0.0f, 1.0f,
		1.0f, 0.0f, 1.0f, 0.0f,
		0.0f, 0.0f, 0.0f, 0.0f,

		0.0f, 1.0f, 0.0f, 1.0f,
		1.0f, 1.0f, 1.0f, 1.0f,
		1.0f, 0.0f, 1.0f, 0.0f
	};

	glGenVertexArrays(1, &quadVAO);
	glGenBuffers(1, &VBO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glBindVertexArray(quadVAO);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(float), 0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

}

void SpriteRenderer::DrawSprite(unsigned int &texture, glm::vec2 positon,
	glm::vec2 size, GLfloat rorate,
	glm::vec3 color)
{
	shader.use();
	glm::mat4 model(1.0f);
	model = glm::translate(model,glm::vec3(positon,0.0f));

	//model = glm::translate()

}
