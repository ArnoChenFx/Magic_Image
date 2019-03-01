#pragma once
#include <glm/glm.hpp>

class Camera
{
public:
	Camera(glm::vec3 position,glm::vec3 target ,glm::vec3 worldup);
	~Camera();

	glm::vec3 Position;
	glm::vec3 Forward;
	glm::vec3 Right;
	glm::vec3 Up;
	glm::vec3 WorldUp;

	glm::mat4 GetViewMatrix();
};

