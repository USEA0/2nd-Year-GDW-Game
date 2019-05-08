#pragma once

#include <string>
#include "Matrix.h"

class Transform
{
public:
	vec3 m_pScale = vec3(1.0f, 1.0f, 1.0f);
	float m_pRotX = 0.0f;
	float m_pRotY = 0.0f;
	float m_pRotZ = 0.0f; // local rotation angles

	vec3 m_pLocalPosition;

	// TODO: Compute these matrices in the Update function
	mat4 m_pLocalRotation;
	mat4 m_pLocalToWorldMatrix;

	Transform();
	~Transform();

	void setPosition(vec3 newPosition);
	void setPositionX(float pos);
	void setPositionY(float pos);
	void setPositionZ(float pos);
	vec3 getPosition();
	float getPositionX();
	float getPositionY();
	float getPositionZ();

	void setRotationX(float newAngle);
	void setRotationY(float newAngle);
	void setRotationZ(float newAngle);
	float getRotationX();
	float getRotationY();
	float getRotationZ();

	vec3 getScale() { return m_pScale; }
	void setScale(float newScale);
	void setScale(vec3 newScale);


	virtual void update(float dt);
	virtual void update();
	
	// Other Properties
	std::string name;
	vec4 color; 
};