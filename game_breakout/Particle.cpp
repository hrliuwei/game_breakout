#include "Particle.h"

ParticleGenerator::ParticleGenerator(Shader* shader, unsigned int texture_2D, GLuint amount)
	:m_shader(shader),
	m_Texture2D(texture_2D),
	m_amount(amount)
{
	init();
}


GLuint lastUnusedParticle = 0;
GLuint ParticleGenerator::firstUnusedParticle()
{
	for (GLuint i = lastUnusedParticle; i < m_amount; ++i)
	{
		if (m_Particle[i].Life <= 0.0f)
		{
			lastUnusedParticle = i;
			return i;
		}
	}

	for (GLuint i = 0; i < lastUnusedParticle; ++i)
	{
		if (m_Particle[i].Life <= 0.0f)
		{
			lastUnusedParticle = i;
			return i;
		}
	}
	lastUnusedParticle = 0;
	return 0;
}

void ParticleGenerator::respawPartcile(Particle& particle, GameObject& object, glm::vec2 offset)
{
	GLfloat random = (rand() % 100 - 50) / 10.f;
	GLfloat rColor = 0.5 + (rand() % 100) / 100.f;
	particle.Position = object.Position  + glm::vec2(random,0.0f);
	particle.Color = glm::vec4(rColor, rColor, rColor, 1.0f);
	particle.Life = 1.0f;
	particle.Velocity = glm::vec2(10.0f,0.0f);



}


void ParticleGenerator::Update(GLfloat dt, GameObject& object, GLuint newParticles, glm::vec2 offset)
{
	for (GLuint i = 0; i < newParticles; ++i)
	{
		int unusedParticle = firstUnusedParticle();
		respawPartcile(m_Particle[unusedParticle], object, offset);
	}
	for (int i = 0; i < m_amount; ++i)
	{
		Particle &p = m_Particle[i];
		p.Life -= dt;
		if (p.Life > 0.0f)
		{
			//p.Position -= p.Velocity*dt;
			//p.Color.a -= dt * 2.5f;
		}
	}
}

void ParticleGenerator::Draw() {
	glBlendFunc(GL_SRC_ALPHA, GL_ONE);
	m_shader->use();
	for (Particle particle:m_Particle)
	{
		if (particle.Life > 0.0f)
		{
			glm::mat4 model(1.0f);
			model = glm::translate(model, glm::vec3(particle.Position, 0.0f));

			model = glm::translate(model, glm::vec3(0.5f*50, 0.5f*50, 0.0f));
			model = glm::rotate(model, 0.0f, glm::vec3(0.0f, 0.0f, 1.0f));
			model = glm::translate(model, glm::vec3(-0.5f*50, -0.5f*50, 0.0f));

			model = glm::scale(model, glm::vec3(glm::vec2(50.0f,50.f), 1.0f));

			m_shader->setMat4("model", model);
			m_shader->setVec3("spriteColor", glm::vec3(0.5f,0.5f,0.5f));
			
			glBindTexture(GL_TEXTURE_2D, m_Texture2D);
			glBindVertexArray(VAO);
			glDrawArrays(GL_TRIANGLES, 0, 6);
			glBindVertexArray(0);
		}
	}
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC1_ALPHA);
}

void ParticleGenerator::init()
{
	GLuint VBO;
	GLfloat particle_quad[] = {
		0.0f, 1.0f, 0.0f, 1.0f,
		1.0f, 0.0f, 1.0f, 0.0f,
		0.0f, 0.0f, 0.0f, 0.0f,

		0.0f, 1.0f, 0.0f, 1.0f,
		1.0f, 1.0f, 1.0f, 1.0f,
		1.0f, 0.0f, 1.0f, 0.0f
	};
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);

	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(particle_quad), particle_quad, GL_STATIC_DRAW);

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(GLfloat), (void*)0);
	glBindVertexArray(0);
	for (GLuint i = 0; i < m_amount; ++i)
	{
		m_Particle.push_back(Particle());
	}
}


