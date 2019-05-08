#pragma once
#include "Transform.h"
#include "Matrix.h"

enum ProjectionType
{
	Perspective,
	Orthographic
};

class Camera : public Transform
{
public:	
	Camera();
	Camera(ProjectionType projType);

	void perspective(
		float fovy, float aspect, 
		float zNear, float zFar);

	void orthographic(
		float left, float right,
		float top, float bottom,
		float zNear, float zFar);

	mat4 getView() const;
	mat4 getProjection() const;

	float m_pNear;
	float m_pFar;
private:
	ProjectionType projectionType = ProjectionType::Perspective;
	mat4 projection;
};