/*******************************************************************
** This code is part of Breakout.
**
** Breakout is free software: you can redistribute it and/or modify
** it under the terms of the CC BY 4.0 license as published by
** Creative Commons, either version 4 of the License, or (at your
** option) any later version.
******************************************************************/
#ifndef RESOURCE_MANAGER_H
#define RESOURCE_MANAGER_H

#include <map>
#include <string>
#include "shader.h"



// A static singleton ResourceManager class that hosts several
// functions to load Textures and Shaders. Each loaded texture
// and/or shader is also stored for future reference by string
// handles. All functions and resources are static and no 
// public constructor is defined.
class ResourceManager
{
 public:
	 static ResourceManager& GetInstance() {
		 static ResourceManager s_resmgr;
		 return s_resmgr;
	 };
 	// Resource storage
 	 std::map<std::string, Shader*>    m_Shaders;
 	 std::map<std::string, unsigned int> Textures;
 	// Loads (and generates) a shader program from file loading vertex, fragment (and geometry) shader's source code. If gShaderFile is not nullptr, it also loads a geometry shader
 	 Shader   LoadShader(const char  *vShaderFile, const char  *fShaderFile, const char *gShaderFile, std::string name);
	// Retrieves a stored sader
 	 Shader   GetShader(std::string name);
 	// Loads (and generates) a texture from file
 	unsigned int LoadTexture(const char *file, std::string name);
 	// Retrieves a stored texture
 	unsigned int GetTexture(std::string name);
 	// Properly de-allocates all loaded resources
 	void      Clear();
// private:
// 	// Private constructor, that is we do not want any actual resource manager objects. Its members and functions should be publicly available (static).
// 	ResourceManager() { }
// 	// Loads and generates a shader from file
 	 
// 	// Loads a single texture from file
 	unsigned int loadTextureFromFile(char const* path);
};

#endif