#pragma once
#include "GameObject.h"
class BallObject :
	public GameObject
{
public:
	GLfloat m_Radius;
	bool m_bStuck;
	BallObject();
	BallObject(glm::vec2 pos, GLfloat radius, glm::vec2 velocity, unsigned int Sprite_texture);
	glm::vec2 Move(GLfloat dt, unsigned int window_width);
	void Reset(glm::vec2 position, glm::vec2 velocity);
};

