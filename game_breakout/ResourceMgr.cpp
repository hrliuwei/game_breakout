/*******************************************************************
** This code is part of Breakout.
**
** Breakout is free software: you can redistribute it and/or modify
** it under the terms of the CC BY 4.0 license as published by
** Creative Commons, either version 4 of the License, or (at your
** option) any later version.
******************************************************************/
#include "ResourceMgr.h"

#include <iostream>
#include <sstream>
#include <fstream>

#include "stb_image.h"

Shader ResourceManager::LoadShader(const char *vShaderFile, const char *fShaderFile, const char *gShaderFile, std::string name)
{
	Shader shader(vShaderFile, fShaderFile, gShaderFile);
	m_Shaders.insert(std::make_pair(name,shader));
	return shader;
}

Shader ResourceManager::GetShader(std::string name)
{
	return m_Shaders[name];
}

 unsigned int ResourceManager::LoadTexture(const char *file, std::string name)
 {
 	Textures[name] = loadTextureFromFile(file);
 	return Textures[name];
 }
// 
 unsigned int ResourceManager::GetTexture(std::string name)
 {
	 return Textures[name];
 }
// 
 void ResourceManager::Clear()
 {
 	// (Properly) delete all shaders	
 	for (auto iter : m_Shaders)
 		glDeleteProgram(iter.second.ID);
 	// (Properly) delete all textures
 	for (auto iter : Textures)
 		glDeleteTextures(1, &iter.second);
 }
 

// 
 unsigned int ResourceManager::loadTextureFromFile(char const* path)
 {
 	// Create Texture object
 	unsigned int texture;
 	glGenTextures(1, &texture);
    
 	int width, height, nrChannels;
 	stbi_set_flip_vertically_on_load(true);
 	unsigned char* data = stbi_load(path, &width, &height, &nrChannels, 0);
 	if (data) {
 		GLenum format;
 		if (nrChannels == 1) {
 			format = GL_RED;
 		}
 		else if (nrChannels == 3) {
 			format = GL_RGB;
 		}
 		else if (nrChannels == 4) {
 			format = GL_RGBA;
 		}
 		glBindTexture(GL_TEXTURE_2D, texture);
 		glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
 		glGenerateMipmap(GL_TEXTURE_2D);
 
 		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
 		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
 		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
 		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
 
 		stbi_image_free(data);
 	}
 	return texture;
 }