#pragma once
#include "GlobalHeader.h"

class Camera
{
public:
	Camera();
	virtual ~Camera();

private:
	int _id;
	glm::vec3 _position;
	bool _orthographic;
};

