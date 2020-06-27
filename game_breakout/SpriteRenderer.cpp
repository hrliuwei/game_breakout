#include "SpriteRenderer.h"


SpriteRenderer::SpriteRenderer(Shader shader)
{
	m_shader = shader;
}


void SpriteRenderer::InitRenderData()
{
	// ≈‰÷√ VAO/VBO
	GLuint VBO;
	GLfloat vertices[] = {
		// Œª÷√     // Œ∆¿Ì
		0.0f, 0.0f, 0.0f, 0.0f,
		0.0f, 1.0f, 0.0f, 1.0f,
		1.0f, 0.0f, 1.0f, 0.0f,

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

void SpriteRenderer::DrawSprite(unsigned int texture, glm::vec2 positon,
	glm::vec2 size, GLfloat rotate,
	glm::vec3 color)
{
	m_shader.use();
	glm::mat4 model(1.0f);
	model = glm::translate(model,glm::vec3(positon,0.0f));

	model = glm::translate(model, glm::vec3(0.5f*size.x, 0.5f*size.y,0.0f));
	model = glm::rotate(model, rotate, glm::vec3(0.0f, 0.0f, 1.0f));
	model = glm::translate(model, glm::vec3(-0.5f*size.x, -0.5f*size.y, 0.0f));

	model = glm::scale(model, glm::vec3(size, 1.0f));

	m_shader.setMat4("model", model);
	m_shader.setVec3("spriteColor", color);

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texture);

	glBindVertexArray(quadVAO);
	glDrawArrays(GL_TRIANGLES, 0, 6);

	glBindVertexArray(0);
}
