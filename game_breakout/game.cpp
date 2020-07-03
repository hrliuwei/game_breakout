/*******************************************************************
** This code is part of Breakout.
**
** Breakout is free software: you can redistribute it and/or modify
** it under the terms of the CC BY 4.0 license as published by
** Creative Commons, either version 4 of the License, or (at your
** option) any later version.
******************************************************************/
#include "game.h"
#include "ResourceMgr.h"
#include "SpriteRenderer.h"
#include <GLFW/glfw3.h>
#include <algorithm>


SpriteRenderer  *g_Renderer;

// 初始化挡板的大小
const glm::vec2 PLAYER_SIZE(100, 20);
// 初始化当班的速率
const GLfloat PLAYER_VELOCITY(500.0f);

GameObject      *Player;

// 初始化球的速度
const glm::vec2 INITIAL_BALL_VELOCITY(50.0f, -350.0f);
// 球的半径
const GLfloat BALL_RADIUS = 12.5f;

BallObject     *Ball;

 Game::Game(GLuint width, GLuint height)
 	: State(GAME_ACTIVE), Keys(), Width(width), Height(height)
 {
 
 }
 
 Game::~Game()
 {
	 
 }
 
 void Game::Init()
 {
	 std::string commonPath = "F:\\PersonGit\\game_breakout\\Resource";
	 ResourceManager::GetInstance().LoadShader("F:\\PersonGit\\game_breakout\\game_breakout\\vertex.vs",
		 "F:\\PersonGit\\game_breakout\\game_breakout\\fragment.fs", nullptr, "sprite");

	 glm::mat4 projection = glm::ortho(0.0f, (GLfloat)Width, (GLfloat)Height, 0.0f, -1.0f, 1.0f);
	 ResourceManager::GetInstance().GetShader("sprite").use();
	 ResourceManager::GetInstance().GetShader("sprite").setInt("image", 0);
	 ResourceManager::GetInstance().GetShader("sprite").setMat4("projection", projection);

	 g_Renderer = new SpriteRenderer(ResourceManager::GetInstance().GetShader("sprite"));
	 ResourceManager::GetInstance().LoadTexture((commonPath + "\\awesomeface.png").c_str(), "face");
	 ResourceManager::GetInstance().LoadTexture((commonPath + "\\background.jpg").c_str(), "background");
	 ResourceManager::GetInstance().LoadTexture((commonPath + "\\block.png").c_str(), "block");
	 ResourceManager::GetInstance().LoadTexture((commonPath + "\\block_solid.png").c_str(), "block_solid");
	 ResourceManager::GetInstance().LoadTexture((commonPath + "\\paddle.png").c_str(), "paddle");


	 GameLevel one; one.Load((commonPath + "\\one.lvl").c_str(), this->Width, this->Height*0.5);
	 GameLevel two; two.Load((commonPath + "\\two.lvl").c_str(), this->Width, this->Height*0.5);
	 GameLevel three; three.Load((commonPath + "\\three.lvl").c_str(), this->Width, this->Height*0.5);
	 GameLevel four; four.Load((commonPath + "\\four.lvl").c_str(), this->Width, this->Height*0.5);
	 m_Levels.push_back(one);
	 m_Levels.push_back(two);
	 m_Levels.push_back(three);
	 m_Levels.push_back(four);
	 m_Level = 0;
	 g_Renderer->InitRenderData();

	 glm::vec2 playerPos = glm::vec2(
		 this->Width / 2 - PLAYER_SIZE.x / 2,
		 this->Height - PLAYER_SIZE.y
	 );
	 Player = new GameObject(playerPos, PLAYER_SIZE, ResourceManager::GetInstance().GetTexture("paddle"));
	 glm::vec2 ballPos = playerPos + glm::vec2(PLAYER_SIZE.x / 2 - BALL_RADIUS, -BALL_RADIUS * 2);
	 Ball = new BallObject(ballPos, BALL_RADIUS, INITIAL_BALL_VELOCITY, ResourceManager::GetInstance().GetTexture("face"));
 }
 
 void Game::Update(GLfloat dt)
 {
	 Ball->Move(dt, Width);
	 DoCollisions();
 }
 
 
 void Game::ProcessInput(GLfloat dt)
 {
	 GLfloat velocity = PLAYER_VELOCITY * dt;
	 if (Keys[GLFW_KEY_A])
	 {
		 if (Player->Position.x >= 0)
		 {
			 Player->Position.x -= velocity;
			 if (Ball->m_bStuck)
			 {
				 Ball->Position.x -= velocity;
			 }
		 }
	 }
	 if (Keys[GLFW_KEY_D])
	 {
		 if (Player->Position.x <= (Width - Player->Size.x))
		 {
			 Player->Position.x += velocity;
			 if (Ball->m_bStuck)
			 {
				 Ball->Position.x += velocity;
			 }
		 }
	 }
	 if (Keys[GLFW_KEY_SPACE])
	 {
		 Ball->m_bStuck = false;
	 }
 }
 
 void Game::Render()
 {
	 g_Renderer->DrawSprite(ResourceManager::GetInstance().GetTexture("background"),
		 glm::vec2(0,0), glm::vec2(Width, Height), 0.0f, glm::vec3(0.0f, 1.0f, 0.0f));

	 Player->Draw(*g_Renderer);
	 m_Levels[m_Level].Draw(*g_Renderer);
	 Ball->Draw(*g_Renderer);
 }

 void Game::DoCollisions()
 {
	 for (GameObject& obj:m_Levels[m_Level].Bricks){
		 if (!obj.Destroyed){
// 			 if (CheckCollisons(*Ball, obj)){
// 				 if (!obj.IsSolid){
// 					 obj.Destroyed = GL_TRUE;
// 				 }
// 			 }
			 Collision collision = CheckCollisons(*Ball, obj);
			 if (std::get<0>(collision)){
				 if (!obj.IsSolid){
					 obj.Destroyed = GL_TRUE;
				 }
				 Direction dir = std::get<1>(collision);
				 if (dir == LEFT || dir == RIGHT){
					 Ball->Velocity.x = -Ball->Velocity.x;
					 GLfloat peneration = Ball->m_Radius - glm::abs(std::get<2>(collision).x);
					 if (dir == LEFT){
						 Ball->Position.x += peneration;
					 }
					 else {
						 Ball->Position.x -= peneration;
					 }					 
				 }
				 else {
					 Ball->Velocity.y = -Ball->Velocity.y;
					 GLfloat peneration = Ball->m_Radius - glm::abs(std::get<2>(collision).y);
					 if (dir == UP){
						 Ball->Position.y += peneration;						 
					 }
					 else {
						 Ball->Position.y -= peneration;
					 }
				 }
			 }
		 }
	 }
 }

 float clamp(float value, float min, float max) {
	 return std::max(min, std::min(max, value));
 }

 bool Game::CheckCollisons(GameObject& one, GameObject& two)
 {
	 bool CollisonsX = (one.Position.x + one.Size.x >= two.Position.x) && (two.Position.x + two.Size.x >= one.Position.x);

	 bool CollisonsY = (one.Position.y + one.Size.y >= two.Position.y) && (two.Position.y + two.Size.y >= one.Position.y);

	 return CollisonsX && CollisonsY;
 }

 Direction VevtorDirection(glm::vec2 target)
 {
	 glm::vec2 compass[] = {
		 glm::vec2(0.0f,1.0f),
		 glm::vec2(0.0f,-1.0f),
		 glm::vec2(-1.0f,0.0f),
		 glm::vec2(1.0f,0.0f)
	 };
	 GLfloat maxValue = 0.0;
	 int best_dir = 0;
	 for (int i = 0; i < 4; ++i) {
		 GLfloat value = glm::abs(glm::dot(compass[i], glm::normalize(target)));
		 if (value > maxValue){
			 maxValue = value;
			 best_dir = i;
		 }
	 }
	 return Direction(best_dir);
 }


 Collision Game::CheckCollisons(BallObject& one, GameObject& two)
 {
 	 glm::vec2 center(one.Position + one.m_Radius);
 	 glm::vec2 aabb_half_extents(two.Size.x / 2, two.Size.y / 2);
 	 glm::vec2 aabb_center(two.Position + aabb_half_extents);
 
 	 glm::vec2 vD = center - aabb_center;
	 glm::vec2 clamped;
	 clamped.x = clamp(vD.x, -aabb_half_extents.x, aabb_half_extents.x);
	 clamped.y = clamp(vD.y, -aabb_half_extents.y, aabb_half_extents.y);
 	 //glm::vec2 clamped =  glm::clamp(vD, -aabb_half_extents, aabb_half_extents);
 
 	 glm::vec2 closest = aabb_center + clamped;
 	 glm::vec2 dv = closest - center;
 	 //return glm::length(dv) < one.m_Radius;
	 if (glm::length(dv) < one.m_Radius){
		 return std::make_tuple(GL_TRUE, VevtorDirection(dv), dv);
	 }
	 else {
		 return std::make_tuple(GL_FALSE, UP, glm::vec2(0, 0));
	 }
	 
 }