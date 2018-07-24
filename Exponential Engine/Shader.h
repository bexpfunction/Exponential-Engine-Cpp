#pragma once
#include "GlobalHeader.h"

class Shader
{
public:
	//Program ID
	unsigned int ID;

	//Constructor
	Shader(const GLchar *pVertexShaderPath, const GLchar *pFragmentShaderPath);
	//Activate shader
	void use();
	//set uniforms
	void setBool(const std::string &name, bool value) const;
	void setInt(const std::string &name, int value) const;
	void setFloat(const std::string &name, float value) const;
	//Destructor
	virtual ~Shader();
};

