#include "BallObject.h"

BallObject::BallObject()
	:GameObject(), m_Radius(12.5f), m_bStuck(true)
{

}

BallObject::BallObject(glm::vec2 pos, GLfloat radius, glm::vec2 velocity, unsigned int Sprite_texture)
	: GameObject(pos, glm::vec2(radius * 2, radius * 2), Sprite_texture, glm::vec3(1.0f), velocity)
	, m_Radius(radius)
	, m_bStuck(true)
{

}

glm::vec2 BallObject::Move(GLfloat dt, unsigned int window_width)
{
	if (!m_bStuck)
	{
		Position += Velocity * dt;
		if (Position.x <= 0.0f)
		{
			Velocity.x = -Velocity.x;
			Position.x = 0.0f;
		}
		else if (Position.x + Size.x >= window_width)
		{
			Velocity.x = -Velocity.x;
			Position.x = window_width - Size.x;
		}
		if (Position.y <= 0.0f)
		{
			Velocity.y = -Velocity.y;
			Position.y = 10.0f;
		}
 		else if (Position.y + Size.y >= 600)
 		{
 			Velocity.y = -Velocity.y;
 			Position.y = 600 - Size.y;
 		}
	}
	//Position = glm::vec2(200, 300);
	return Position;
}

void BallObject::Reset(glm::vec2 position, glm::vec2 velocity)
{
	Position = position;
	Velocity = velocity;
	m_bStuck = true;
}

