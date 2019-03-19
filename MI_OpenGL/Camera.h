#pragma once
#include <glm/glm.hpp>
#include "mi_opengl_global.h"
//#define GLM_ENABLE_EXPERIMENTAL
//#include "glm/gtx/quaternion.hpp"
//#include "glm/gtc/quaternion.hpp"
//#include "glm/common.hpp"


class MI_OPENGL_EXPORT Camera
{
public:
	Camera(glm::vec3 position,glm::vec3 target ,glm::vec3 worldup);
	~Camera();

	glm::vec3 Position;
	glm::vec3 Forward;
	glm::vec3 Right;
	glm::vec3 Up;
	glm::vec3 WorldUp;

	glm::vec3 Target;
	glm::mat4 CameraMatrix;

	const int MODE_MOVE = 0;
	const int MODE_ROTATE = 1;
	const int MODE_ZOOM = 2;
	int MODE;

	
	float globalSpeed = 1 / 15;
	float speedX = 0;
	float speedY = 0;
	float speedZ = 0;

	float distance;

	void updateCamPos();
	glm::mat4 GetViewMatrix();
	void setStop();
	void updateCamVectors();
	void computeDistance();

};

