#include "Camera.h"
#include "glm/gtc/matrix_transform.hpp"
//#include "glm/gtx/quaternion.hpp"
#include "glm/gtc/quaternion.hpp"
//#include "glm/common.hpp"
#include <iostream>

Camera::Camera(glm::vec3 position, glm::vec3 target, glm::vec3 worldup)
{
	Position = position;
	WorldUp = worldup;

	Forward = glm::normalize(target-position);
	Right = glm::normalize(glm::cross(Forward, WorldUp));
	Up = glm::normalize(glm::cross(Forward, Right));
	
	Target = Position + Forward;

	CameraMatrix = glm::mat4(1.0f);

	//Rot = glm::quat();
	MODE = MODE_MOVE;
}

Camera::Camera(glm::vec3 position, float pitch, float yaw, glm::vec3 worldup)
{
	Position = position;
	WorldUp = worldup;

	Pitch = glm::radians(pitch);
	Yaw = glm::radians(yaw);

	// make sure that when pitch is out of bounds, screen doesn't get flipped
	//if (Pitch > 89.0f)
	//	Pitch = 89.0f;
	//if (Pitch < -89.0f)
	//	Pitch = -89.0f;

	updateCamVectors();
}

glm::mat4 Camera::GetViewMatrix()
{
	if (MODE == MODE_MOVE || MODE == MODE_ZOOM)
		Target = Position + Forward;

	return glm::lookAt(Position, Target,WorldUp);
	
}

void Camera::setStop()
{
	speedX = 0;
	speedY = 0;
	speedZ = 0;
}

void Camera::processMovement(float deltaX, float deltaY)
{
	Pitch += glm::radians(deltaY) / (float)10.0;
	Yaw += glm::radians(deltaX) / (float)10.0;
	updateCamVectors();
}

void Camera::updateCamPos()
{
	if (MODE != MODE_ROTATE)
	{
		Position += Forward * speedZ / (float)20.0;
	}
	
	Position -= Right * speedX / (float)40.0;
	Position -= Up * speedY / (float)40.0;

	float dis = glm::distance(Position, Target);

	if (dis != distance && MODE == MODE_ROTATE)
	{
		Position += Forward * (dis - distance);
	}
}


void Camera::updateCamVectors()
{
	if (MODE == MODE_ROTATE)
		Forward = Target - Position;

	Forward = glm::normalize(Forward);
	Right = glm::normalize(glm::cross(Forward, WorldUp));
	Up = glm::normalize(glm::cross(Forward, Right));
}

void Camera::computeDistance()
{
	distance = glm::distance(Position, Target);
}

Camera::~Camera()
{
	std::cout << "camera delete" << std::endl;
}
