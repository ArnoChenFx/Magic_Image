#pragma once
#include <glm/glm.hpp>

class Camera
{
public:
	Camera(glm::vec3 position,glm::vec3 target ,glm::vec3 worldup);
	Camera(glm::vec3 position,float pitch,float yaw ,glm::vec3 worldup);

	~Camera();

	glm::vec3 Position;
	glm::vec3 Forward;
	glm::vec3 Right;
	glm::vec3 Up;
	glm::vec3 WorldUp;

	float Pitch;
	float Yaw;
	
	float globalSpeed = 1 / 15;
	
	float speedX = 0;
	float speedY = 0;
	float speedZ = 0;

	void processMovement(float deltaX,float deltaY);
	void updateCamPos();
	glm::mat4 GetViewMatrix();
	void setStop();

private:
	void updateCamVectors();
};

