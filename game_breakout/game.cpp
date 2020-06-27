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

 Game::Game(GLuint width, GLuint height)
 	: State(GAME_ACTIVE), Keys(), Width(width), Height(height)
 {
 
 }
 
 Game::~Game()
 {
	 
 }
 
 void Game::Init()
 {
	 ResourceManager::GetInstance().LoadShader("D:\\Advantage\\game_breakout\\game_breakout\\vertex.vs",
		 "D:\\Advantage\\game_breakout\\game_breakout\\fragment.fs", nullptr, "sprite");

	 glm::mat4 projection = glm::ortho(0.0f, (GLfloat)Width, (GLfloat)Height, 0.0f, -1.0f, 1.0f);
	 ResourceManager::GetInstance().GetShader("sprite").use();
	 ResourceManager::GetInstance().GetShader("sprite").setInt("image", 0);
	 ResourceManager::GetInstance().GetShader("sprite").setMat4("projection", projection);

	 g_Renderer = new SpriteRenderer(ResourceManager::GetInstance().GetShader("sprite"));
	 ResourceManager::GetInstance().LoadTexture("D:\\Advantage\\game_breakout\\Resource\\awesomeface.png", "face");
	 ResourceManager::GetInstance().LoadTexture("D:\\Advantage\\game_breakout\\Resource\\background.jpg", "background");
	 ResourceManager::GetInstance().LoadTexture("D:\\Advantage\\game_breakout\\Resource\\block.png", "block");
	 ResourceManager::GetInstance().LoadTexture("D:\\Advantage\\game_breakout\\Resource\\block_solid.png", "block_solid");
	 ResourceManager::GetInstance().LoadTexture("D:\\Advantage\\game_breakout\\Resource\\paddle.png", "paddle");


	 GameLevel one; one.Load("D:\\Advantage\\game_breakout\\Resource\\one.lvl", this->Width, this->Height*0.5);
	 GameLevel two; two.Load("D:\\Advantage\\game_breakout\\Resource\\two.lvl", this->Width, this->Height*0.5);
	 GameLevel three; three.Load("D:\\Advantage\\game_breakout\\Resource\\three.lvl", this->Width, this->Height*0.5);
	 GameLevel four; four.Load("D:\\Advantage\\game_breakout\\Resource\\four.lvl", this->Width, this->Height*0.5);
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
 }
 
 void Game::Update(GLfloat dt)
 {
 
 }
 
 
 void Game::ProcessInput(GLfloat dt)
 {
	 GLfloat velocity = PLAYER_VELOCITY * dt;
	 if (Keys[GLFW_KEY_A])
	 {
		 if (Player->Position.x >= 0)
		 {
			 Player->Position.x -= velocity;
		 }
	 }
	 if (Keys[GLFW_KEY_D])
	 {
		 if (Player->Position.x <= (Width - Player->Size.x))
		 {
			 Player->Position.x += velocity;
		 }
	 }
 }
 
 void Game::Render()
 {
	 g_Renderer->DrawSprite(ResourceManager::GetInstance().GetTexture("background"),
		 glm::vec2(0,0), glm::vec2(Width, Height), 0.0f, glm::vec3(0.0f, 1.0f, 0.0f));

	 Player->Draw(*g_Renderer);
	 m_Levels[m_Level].Draw(*g_Renderer);
 }