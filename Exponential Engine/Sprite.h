#pragma once
#include "GlobalHeader.h"

class Sprite
{
public:
	Sprite(glm::vec2 position, glm::vec2 size);
	
	glm::vec2 GetPosition() { return _position; }
	glm::vec2 GetSize() { return _size; }
	void SetPosition(glm::vec2 position) { _position = position; }
	void SetSize(glm::vec2 size) { _size = size; }
	unsigned int GetID() { return _id; }
	void Draw();

	~Sprite();
	
private:
	unsigned int _id, _VAO, _VBO, _EBO;
	glm::vec2 _size, _position;
	Shader *_shader;
};

