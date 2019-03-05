#include "Cameras.h"
#include "glm/gtc/matrix_transform.hpp"


Camera::Camera(glm::vec3 position, glm::vec3 target, glm::vec3 worldup)
{
	Position = position;
	WorldUp = worldup;

	Forward = glm::normalize(target-position);
	Right = glm::normalize(glm::cross(Forward, WorldUp));
	Up = glm::normalize(glm::cross(Forward, Right));
	
}

Camera::Camera(glm::vec3 position, float pitch, float yaw, glm::vec3 worldup)
{
	Position = position;
	WorldUp = worldup;

	Pitch = glm::radians(pitch);
	Yaw = glm::radians(yaw);

	updateCamVectors();
}

glm::mat4 Camera::GetViewMatrix()
{
	return glm::lookAt(Position,Position+Forward,WorldUp);
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
	Position += Forward * speedZ / (float)20.0;
	Position -= Right * speedX / (float)40.0;
	Position -= Up * speedY / (float)40.0;
}


void Camera::updateCamVectors()
{
	// make sure that when pitch is out of bounds, screen doesn't get flipped
	if (Pitch > 89.0f)
		Pitch = 89.0f;
	if (Pitch < -89.0f)
		Pitch = -89.0f;


	Forward.x = glm::cos(Pitch)*glm::sin(Yaw);
	Forward.y = glm::sin(Pitch);
	Forward.z = glm::cos(Pitch)*glm::cos(Yaw);

	Right = glm::normalize(glm::cross(Forward, WorldUp));
	Up = glm::normalize(glm::cross(Forward, Right));
}

Camera::~Camera()
{
}
