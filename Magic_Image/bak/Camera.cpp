#include "Camera.h"
#include "glm/gtc/matrix_transform.hpp"

Camera::Camera(QVector3D position, QVector3D target, QVector3D worldup)
{
	Position = position;
	WorldUp = worldup;

	Forward = target-position;
	Forward.normalize();
	Right = QVector3D::crossProduct(Forward, WorldUp);
	Right.normalize();
	Up = QVector3D::crossProduct(Forward, Right);
	Up.normalize();
}

Camera::Camera(QVector3D position, float pitch, float yaw, QVector3D worldup)
{
	Position = position;
	WorldUp = worldup;

	Pitch = glm::radians(pitch);
	Yaw = glm::radians(yaw);

	updateCamVectors();
}

QMatrix4x4 Camera::GetViewMatrix()
{
	QMatrix4x4 matrix;
	matrix.lookAt(Position, Position + Forward, WorldUp);
	return matrix;
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

	Forward = QVector3D(cos(Pitch)*sin(Yaw), sin(Pitch), cos(Pitch)*cos(Yaw));


	Right = QVector3D::crossProduct(Forward, WorldUp);
	Right.normalize();
	Up = QVector3D::crossProduct(Forward, Right);
	Up.normalize();
}

Camera::~Camera()
{
}
