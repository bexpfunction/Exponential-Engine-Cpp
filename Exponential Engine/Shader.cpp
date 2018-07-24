#include "Shader.h"

Shader::Shader(const GLchar *pVertexShaderPath, const GLchar *pFragmentShaderPath)
{
	//Get the source codes from file path
	std::string vertexCode;
	std::string fragmentCode;
	std::ifstream vShaderFile;
	std::ifstream fShaderFile;

	//ifstream can throw exceptions
	vShaderFile.exceptions(std::ifstream::failbit || std::ifstream::badbit);
	fShaderFile.exceptions(std::ifstream::failbit || std::ifstream::badbit);

	//Reading from file part
	try {
		//Open files
		vShaderFile.open(pVertexShaderPath);
		fShaderFile.open(pFragmentShaderPath);
		std::stringstream vShaderStream, fShaderStream;
		//Read file's buffer contents into streams
		vShaderStream << vShaderFile.rdbuf();
		fShaderStream << fShaderFile.rdbuf();
		//Close files
		vShaderFile.close();
		fShaderFile.close();
		//Convert streams into strings
		vertexCode = vShaderStream.str();
		fragmentCode = fShaderStream.str();
		//Print the codes for debug
		std::cout << "Vertex shader code: " << std::endl << vertexCode << std::endl;
		std::cout << "Fragment shader code: " << std::endl << fragmentCode << std::endl;
	}
	catch (std::ifstream::failure e) {
		std::cout << "ERROR!!! SHADER FILE COULDN'T BE READ SUCCESFULLY!!! : " << e.code() << std::endl;
	}
	//Get the char arrays for shader codes
	const char *vShaderCode = vertexCode.c_str();
	const char *fShaderCode = fragmentCode.c_str();

	//Compile shaders
	unsigned int vertex, fragment;
	int success;
	char infoLog[512];

	//Vertex Shader
	vertex = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertex, 1, &vShaderCode, NULL);
	glCompileShader(vertex);
	//Check for errors
	glGetShaderiv(vertex, GL_COMPILE_STATUS, &success);
	if (!success) {
		glGetShaderInfoLog(vertex, 512, NULL, infoLog);
		std::cout << "ERRORR!!! VERTEX SHADER COULDN'T BE COMPILED" << std::endl << "Shader info log: " << infoLog << std::endl;
	}
	else {
		std::cout << "SUCCESS!!! VERTEX SHADER IS COMPILED!!!" << std::endl;
	}

	//Fragment Shader
	fragment = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragment, 1, &fShaderCode, NULL);
	glCompileShader(fragment);
	//Check for errors
	glGetShaderiv(fragment, GL_COMPILE_STATUS, &success);
	if (!success) {
		glGetShaderInfoLog(fragment, 512, NULL, infoLog);
		std::cout << "ERRORR!!! FRAGMENT SHADER COULDN'T BE COMPILED" << std::endl << "Shader info log: " << infoLog << std::endl;
	}
	else {
		std::cout << "SUCCESS!!! FRAGMENT SHADER IS COMPILED!!!" << std::endl;
	}

	//Create program and link the shaders
	ID = glCreateProgram();
	glAttachShader(ID, vertex);
	glAttachShader(ID, fragment);
	glLinkProgram(ID);
	//Check for link errors
	glGetProgramiv(ID, GL_LINK_STATUS, &success);
	if (!success) {
		glGetProgramInfoLog(ID, 512, NULL, infoLog);
		std::cout << "ERRORR!!! SHADER PROGRAM COULDN'T BE LINKED" << std::endl << "Program info log: " << infoLog << std::endl;
	}
	else {
		std::cout << "SUCCESS!!! BOTH SHADERS HAVE BEEN LINKED WITH THE PROGRAM!!!" << std::endl;
	}
	//Delete the shaders
	glDeleteShader(vertex);
	glDeleteShader(fragment);
}

void Shader::use()
{
	glUseProgram(ID);
}

void Shader::setBool(const std::string & name, bool value) const
{
	glUniform1i(glGetUniformLocation(ID, name.c_str()), (int)value);
}

void Shader::setInt(const std::string & name, int value) const
{
	glUniform1i(glGetUniformLocation(ID, name.c_str()), value);
}

void Shader::setFloat(const std::string & name, float value) const
{
	//std::cout << "Location of " << name << " is " << glGetUniformLocation(ID, name.c_str())<<std::endl;
	glUniform1f(glGetUniformLocation(ID, name.c_str()), value);
}


Shader::~Shader()
{
}
