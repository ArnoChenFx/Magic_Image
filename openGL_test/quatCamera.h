#pragma once
#include <glm/glm.hpp>
#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/transform.hpp>
#include <glm/gtx/quaternion.hpp>
#include <glm/gtc/quaternion.hpp>

class quatCamera
{
public:
	quatCamera();
	quatCamera(float left, float right, float bottom, float top, float zNear, float zFar);
	quatCamera(float fieldOfViewY, float aspectRatio, float zNear, float zFar);
	~quatCamera();

	// Setters
	void setPosition(float x, float y, float z);
	void setPosition(const glm::vec3 &v);

	// Getters
	glm::vec3 getPosition() const;
	glm::vec3 getLeftDirection() const;
	glm::vec3 getUpDirection() const;
	glm::vec3 getForwardDirection() const;
	glm::quat getOrientation() const;
	glm::mat4 getViewMatrix() const;

	// Actions
	void lookAt(const glm::vec3 & center);
	void lookAt(float centerX, float centerY, float centerZ);
	void lookAt(const glm::vec3 & eye,
	const glm::vec3 & center,
	const glm::vec3 & up);
	void roll(float angle);
	void pitch(float angle);
	void yaw(float angle);
	void rotate(float angle, const glm::vec3 & axis);
	void translate(float x, float y, float z);
	void translate(const glm::vec3 &v);
	void translateLocal(float left, float up, float forward);
	void translateLocal(const glm::vec3 &v);

private:
	glm::vec3 eyePosition; // Location of camera in world coordinates.
	glm::quat orientation; // Orientation of camera basis vectors specified in world coordinates.

	glm::vec3 l; // Camera's left direction vector, given in world coordinates.
	glm::vec3 u; // Camera's up direction vector, given in world coordinates.
	glm::vec3 f; // Camera's forward direction vector, given in world coordinates.

	mutable bool recalcViewMatrix;
	mutable glm::mat4 viewMatrix;

	unsigned short rotationHitCount;

	// Normalize Camera vectors after rotating this many times.
	static const unsigned short rotationHitCountMax = 1000;

	void initLocalCoordinateSystem();
	void registerRotation();
	void normalizeCamera();
};