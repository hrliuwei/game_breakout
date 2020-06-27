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

SpriteRenderer  *g_Renderer;

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

	 g_Renderer->InitRenderData();

 }
 
 void Game::Update(GLfloat dt)
 {
 
 }
 
 
 void Game::ProcessInput(GLfloat dt)
 {
 
 }
 
 void Game::Render()
 {
	 g_Renderer->DrawSprite(ResourceManager::GetInstance().GetTexture("face"),
		 glm::vec2(200, 200), glm::vec2(300, 400), 45.0f, glm::vec3(0.0f, 1.0f, 0.0f));
 }