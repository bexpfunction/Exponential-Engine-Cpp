#include "Sprite.h"



Sprite::Sprite(glm::vec2 position, glm::vec2 size)
{
	//Set private variables
	_position = position;
	_size = size;

	//Construct Sprite Quad(anchor at middle center)
	float vertices[] = {
		(_position.x - size.x / 2.0f), (_position.y - size.y / 2.0f), 0.0f,		//Top left vertex
		(_position.x + size.x / 2.0f), (_position.y - size.y / 2.0f), 0.0f,		//Top right vertex
		(_position.x - size.x / 2.0f), (_position.y + size.y / 2.0f), 0.0f,		//Bottom left vertex
		(_position.x + size.x / 2.0f), (_position.y + size.y / 2.0f), 0.0f		//Bottom right vertex
	};

	int indices[] = {
		0, 1, 2,	//Left triangle
		1, 3, 2		//Right triangle
	};

	//VBO and VAO
	glGenVertexArrays(1, &_VAO);
	_id = _VAO;
	glGenBuffers(1, &_VBO);
	glGenBuffers(1, &_EBO);

	//Bind vertex arrays
	glBindVertexArray(_VAO);

	//Then bind buffers to vertex arrays
	glBindBuffer(GL_ARRAY_BUFFER, _VBO);
	//Then bind data to buffers
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	//Then bind element array
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	//Set vertex attribute pointers offsets
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	//Unbind vbo
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	//Unbind vao
	glBindVertexArray(0);
}


void Sprite::Draw()
{
	_shader->setVec2f("worldPosition", _position);
	_shader->use();
	glBindVertexArray(_VAO);
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);
	_shader->stopUse();
	
}

Sprite::~Sprite()
{
	//Dealloc all buffers and objects
	glDeleteVertexArrays(1, &_VAO);
	glDeleteBuffers(1, &_VBO);
	glDeleteBuffers(1, &_EBO);

	_shader = NULL;
	delete _shader;
}
