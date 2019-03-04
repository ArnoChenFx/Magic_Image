#pragma once
//#include <glm/glm.hpp>
#include <qmatrix4x4.h>
#include <qvector3d.h>
class Camera
{
public:
	Camera(QVector3D position, QVector3D target , QVector3D worldup);
	Camera(QVector3D position,float pitch,float yaw , QVector3D worldup);

	~Camera();

	QVector3D Position;
	QVector3D Forward;
	QVector3D Right;
	QVector3D Up;
	QVector3D WorldUp;

	float Pitch;
	float Yaw;
	
	float globalSpeed = 1 / 15;
	
	float speedX = 0;
	float speedY = 0;
	float speedZ = 0;

	void processMovement(float deltaX,float deltaY);
	void updateCamPos();
	QMatrix4x4 GetViewMatrix();
	void setStop();

private:
	void updateCamVectors();
};

