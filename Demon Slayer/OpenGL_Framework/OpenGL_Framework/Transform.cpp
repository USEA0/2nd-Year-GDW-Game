#include "Transform.h"

Transform::Transform()
	: m_pScale(1.0f),
	color(vec4(1.0f))
{
}

Transform::~Transform() {}

void Transform::setPosition(vec3 newPosition)
{
	m_pLocalPosition = newPosition;
}
void Transform::setPositionX(float pos)
{
	m_pLocalPosition.x = pos;
}
void Transform::setPositionY(float pos)
{
	m_pLocalPosition.y = pos;
}
void Transform::setPositionZ(float pos)
{
	m_pLocalPosition.z = pos;
}

void Transform::setRotationX(float newAngle)
{
	m_pRotX = newAngle;
}

void Transform::setRotationY(float newAngle)
{
	m_pRotY = newAngle;
}

void Transform::setRotationZ(float newAngle)
{
	m_pRotZ = newAngle;
}

void Transform::setScale(float newScale)
{
	m_pScale = vec3(newScale, newScale, newScale);
}

void Transform::setScale(vec3 newScale)
{
	m_pScale = newScale;
}

vec3 Transform::getPosition()
{
	return m_pLocalPosition;
}

float Transform::getPositionX()
{
	return m_pLocalPosition.x;
}

float Transform::getPositionY()
{
	return m_pLocalPosition.y;
}

float Transform::getPositionZ()
{
	return m_pLocalPosition.z;
}

float Transform::getRotationX()
{
	return m_pRotX;
}

float Transform::getRotationY()
{
	return m_pRotY;
}

float Transform::getRotationZ()
{
	return m_pRotZ;
}

void Transform::update(float dt)
{
	// Create 4x4 transformation matrix

	// Create rotation matrix

	mat4 rx; 
	mat4 ry; 
	mat4 rz; 

	rx.RotateX(m_pRotX);
	ry.RotateY(m_pRotY);
	rz.RotateZ(m_pRotZ);
	// Note: pay attention to rotation order, ZYX is not the same as XYZ
	m_pLocalRotation = rz * ry * rx;

	// Create translation matrix
	mat4 tran;
	tran.Translate(m_pLocalPosition);

	// Create scale matrix
	mat4 scale; 
	scale.Scale(m_pScale);

	// Combine all above transforms into a single matrix
	// This is the local transformation matrix, ie. where is this game object relative to it's parent
	// If a game object has no parent (it is a root node) then its local transform is also it's global transform
	// If a game object has a parent, then we must apply the parent's transform
	m_pLocalToWorldMatrix = tran * m_pLocalRotation * scale;
}

void Transform::update()
{
	// Create 4x4 transformation matrix

	// Create rotation matrix

	mat4 rx;
	mat4 ry;
	mat4 rz;

	rx.RotateX(m_pRotX);
	ry.RotateY(m_pRotY);
	rz.RotateZ(m_pRotZ);
	// Note: pay attention to rotation order, ZYX is not the same as XYZ
	m_pLocalRotation = rz * ry * rx;

	// Create translation matrix
	mat4 tran;
	tran.Translate(m_pLocalPosition);

	// Create scale matrix
	mat4 scale;
	scale.Scale(m_pScale);

	// Combine all above transforms into a single matrix
	// This is the local transformation matrix, ie. where is this game object relative to it's parent
	// If a game object has no parent (it is a root node) then its local transform is also it's global transform
	// If a game object has a parent, then we must apply the parent's transform
	m_pLocalToWorldMatrix = tran * m_pLocalRotation * scale;
}