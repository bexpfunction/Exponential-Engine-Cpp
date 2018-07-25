#pragma once
#include "GlobalHeader.h"

class Shader
{
public:
	//Program ID
	unsigned int ID;

	//Constructor
	Shader();
	Shader(const GLchar *pVertexShaderPath, const GLchar *pFragmentShaderPath);
	//Activate shader
	void use();
	void stopUse();
	//set uniforms
	void setBool(const std::string &name, bool value) const;
	void setInt(const std::string &name, int value) const;
	void setFloat(const std::string &name, float value) const;
	void setVec2f(const std::string &name, glm::vec2 value) const;
	void setVec3f(const std::string &name, glm::vec3 value) const;
	//Destructor
	virtual ~Shader();
};

