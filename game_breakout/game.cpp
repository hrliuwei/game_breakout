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


SpriteRenderer  *g_Renderer;

// 初始化挡板的大小
const glm::vec2 PLAYER_SIZE(100, 20);
// 初始化当班的速率
const GLfloat PLAYER_VELOCITY(500.0f);

GameObject      *Player;

// 初始化球的速度
const glm::vec2 INITIAL_BALL_VELOCITY(100.0f, -350.0f);
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
			 if (CheckCollisons(*Ball, obj)){
				 if (!obj.IsSolid){
					 obj.Destroyed = GL_TRUE;
				 }
			 }
		 }
	 }
 }

 bool Game::CheckCollisons(GameObject& one, GameObject& two)
 {
	 bool CollisonsX = (one.Position.x + one.Size.x >= two.Position.x) && (two.Position.x + two.Size.x >= one.Position.x);

	 bool CollisonsY = (one.Position.y + one.Size.y >= two.Position.y) && (two.Position.y + two.Size.y >= one.Position.y);

	 return CollisonsX && CollisonsY;
 }