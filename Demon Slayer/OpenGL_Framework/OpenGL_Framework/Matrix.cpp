#include <math.h>
#include "Matrix.h"

float PI = 3.1415f;

mat4 mat4::operator*(mat4 a) const
{
	mat4 temp;
	temp.data[0] = data[0] * a.data[0] + data[4] * a.data[1] + data[8] * a.data[2] + data[12] * a.data[3];
	temp.data[1] = data[1] * a.data[0] + data[5] * a.data[1] + data[9] * a.data[2] + data[13] * a.data[3];
	temp.data[2] = data[2] * a.data[0] + data[6] * a.data[1] + data[10] * a.data[2] + data[14] * a.data[3];
	temp.data[3] = data[3] * a.data[0] + data[7] * a.data[1] + data[11] * a.data[2] + data[15] * a.data[3];

	temp.data[4] = data[0] * a.data[4] + data[4] * a.data[5] + data[8] * a.data[6] + data[12] * a.data[7];
	temp.data[5] = data[1] * a.data[4] + data[5] * a.data[5] + data[9] * a.data[6] + data[13] * a.data[7];
	temp.data[6] = data[2] * a.data[4] + data[6] * a.data[5] + data[10] * a.data[6] + data[14] * a.data[7];
	temp.data[7] = data[3] * a.data[4] + data[7] * a.data[5] + data[11] * a.data[6] + data[15] * a.data[7];

	temp.data[8] = data[0] * a.data[8] + data[4] * a.data[9] + data[8] * a.data[10] + data[12] * a.data[11];
	temp.data[9] = data[1] * a.data[8] + data[5] * a.data[9] + data[9] * a.data[10] + data[13] * a.data[11];
	temp.data[10] = data[2] * a.data[8] + data[6] * a.data[9] + data[10] * a.data[10] + data[14] * a.data[11];
	temp.data[11] = data[3] * a.data[8] + data[7] * a.data[9] + data[11] * a.data[10] + data[15] * a.data[11];

	temp.data[12] = data[0] * a.data[12] + data[4] * a.data[13] + data[8] * a.data[14] + data[12] * a.data[15];
	temp.data[13] = data[1] * a.data[12] + data[5] * a.data[13] + data[9] * a.data[14] + data[13] * a.data[15];
	temp.data[14] = data[2] * a.data[12] + data[6] * a.data[13] + data[10] * a.data[14] + data[14] * a.data[15];
	temp.data[15] = data[3] * a.data[12] + data[7] * a.data[13] + data[11] * a.data[14] + data[15] * a.data[15];
	return temp;
}

vec4 mat4::operator*(vec4 a) const
{
	vec4 temp;
	temp.x = data[0] * a.x + data[4] * a.y + data[8] * a.z + data[12] * a.w;
	temp.y = data[1] * a.x + data[5] * a.y + data[9] * a.z + data[13] * a.w;
	temp.z = data[2] * a.x + data[6] * a.y + data[10] * a.z + data[14] * a.w;
	temp.w = data[3] * a.x + data[7] * a.y + data[11] * a.z + data[15] * a.w;
	return temp;
}

mat4 mat4::operator*(float scalar) const
{
	mat4 temp;
	for (int i = 0; i < 16; i++)
	{
		temp.data[i] = data[i] * scalar;
	}
	return temp;
}

bool mat4::operator==(mat4 a) const
{
	if (data[0] == a.data[0] && data[4] == a.data[4] && data[8] == a.data[8] && data[12] == a.data[12] &&
		data[1] == a.data[1] && data[5] == a.data[5] && data[9] == a.data[9] && data[13] == a.data[13] &&
		data[2] == a.data[2] && data[6] == a.data[6] && data[10] == a.data[10] && data[14] == a.data[14] &&
		data[3] == a.data[3] && data[7] == a.data[7] && data[11] == a.data[11] && data[15] == a.data[15])
		return true;
	else
		return false;
}

bool mat4::operator!=(mat4 a) const
{
	if (data[0] != a.data[0] || data[4] != a.data[4] || data[8] != a.data[8] || data[12] != a.data[12] ||
		data[1] != a.data[1] || data[5] != a.data[5] || data[9] != a.data[9] || data[13] != a.data[13] ||
		data[2] != a.data[2] || data[6] != a.data[6] || data[10] != a.data[10] || data[14] != a.data[14] ||
		data[3] != a.data[3] || data[7] != a.data[7] || data[11] != a.data[11] || data[15] != a.data[15])
		return true;
	else
		return false;
}

mat4 mat4::GetInverse() const
{
	mat4 temp;
	temp.data[0] = data[5] * data[10] * data[15] -
		data[5] * data[11] * data[14] -
		data[9] * data[6] * data[15] +
		data[9] * data[7] * data[14] +
		data[13] * data[6] * data[11] -
		data[13] * data[7] * data[10];

	temp.data[4] = -data[4] * data[10] * data[15] +
		data[4] * data[11] * data[14] +
		data[8] * data[6] * data[15] -
		data[8] * data[7] * data[14] -
		data[12] * data[6] * data[11] +
		data[12] * data[7] * data[10];

	temp.data[8] = data[4] * data[9] * data[15] -
		data[4] * data[11] * data[13] -
		data[8] * data[5] * data[15] +
		data[8] * data[7] * data[13] +
		data[12] * data[5] * data[11] -
		data[12] * data[7] * data[9];

	temp.data[12] = -data[4] * data[9] * data[14] +
		data[4] * data[10] * data[13] +
		data[8] * data[5] * data[14] -
		data[8] * data[6] * data[13] -
		data[12] * data[5] * data[10] +
		data[12] * data[6] * data[9];

	temp.data[1] = -data[1] * data[10] * data[15] +
		data[1] * data[11] * data[14] +
		data[9] * data[2] * data[15] -
		data[9] * data[3] * data[14] -
		data[13] * data[2] * data[11] +
		data[13] * data[3] * data[10];

	temp.data[5] = data[0] * data[10] * data[15] -
		data[0] * data[11] * data[14] -
		data[8] * data[2] * data[15] +
		data[8] * data[3] * data[14] +
		data[12] * data[2] * data[11] -
		data[12] * data[3] * data[10];

	temp.data[9] = -data[0] * data[9] * data[15] +
		data[0] * data[11] * data[13] +
		data[8] * data[1] * data[15] -
		data[8] * data[3] * data[13] -
		data[12] * data[1] * data[11] +
		data[12] * data[3] * data[9];

	temp.data[13] = data[0] * data[9] * data[14] -
		data[0] * data[10] * data[13] -
		data[8] * data[1] * data[14] +
		data[8] * data[2] * data[13] +
		data[12] * data[1] * data[10] -
		data[12] * data[2] * data[9];

	temp.data[2] = data[1] * data[6] * data[15] -
		data[1] * data[7] * data[14] -
		data[5] * data[2] * data[15] +
		data[5] * data[3] * data[14] +
		data[13] * data[2] * data[7] -
		data[13] * data[3] * data[6];

	temp.data[6] = -data[0] * data[6] * data[15] +
		data[0] * data[7] * data[14] +
		data[4] * data[2] * data[15] -
		data[4] * data[3] * data[14] -
		data[12] * data[2] * data[7] +
		data[12] * data[3] * data[6];

	temp.data[10] = data[0] * data[5] * data[15] -
		data[0] * data[7] * data[13] -
		data[4] * data[1] * data[15] +
		data[4] * data[3] * data[13] +
		data[12] * data[1] * data[7] -
		data[12] * data[3] * data[5];

	temp.data[14] = -data[0] * data[5] * data[14] +
		data[0] * data[6] * data[13] +
		data[4] * data[1] * data[14] -
		data[4] * data[2] * data[13] -
		data[12] * data[1] * data[6] +
		data[12] * data[2] * data[5];

	temp.data[3] = -data[1] * data[6] * data[11] +
		data[1] * data[7] * data[10] +
		data[5] * data[2] * data[11] -
		data[5] * data[3] * data[10] -
		data[9] * data[2] * data[7] +
		data[9] * data[3] * data[6];

	temp.data[7] = data[0] * data[6] * data[11] -
		data[0] * data[7] * data[10] -
		data[4] * data[2] * data[11] +
		data[4] * data[3] * data[10] +
		data[8] * data[2] * data[7] -
		data[8] * data[3] * data[6];

	temp.data[11] = -data[0] * data[5] * data[11] +
		data[0] * data[7] * data[9] +
		data[4] * data[1] * data[11] -
		data[4] * data[3] * data[9] -
		data[8] * data[1] * data[7] +
		data[8] * data[3] * data[5];

	temp.data[15] = data[0] * data[5] * data[10] -
		data[0] * data[6] * data[9] -
		data[4] * data[1] * data[10] +
		data[4] * data[2] * data[9] +
		data[8] * data[1] * data[6] -
		data[8] * data[2] * data[5];

	float det = data[0] * temp.data[0] + data[1] * temp.data[4] + data[2] * temp.data[8] + data[3] * temp.data[12];
	if (det != 0) {
		det = 1.0f / det;

		temp = temp * det;
		return temp;
	}
	else
		return *this;
}

vec3 mat4::GetDirectionVec() const
{
	vec3 temp;
	temp.x = data[2] * -1.0f;
	temp.y = data[6];
	temp.z = data[10];
	temp.Normalize();
	return temp;
}

mat3 mat4::GetRotationMat() const
{
	mat3 temp;
	temp.data[0] = data[0];
	temp.data[1] = data[1];
	temp.data[2] = data[2];

	temp.data[3] = data[4];
	temp.data[4] = data[5];
	temp.data[5] = data[6];

	temp.data[6] = data[8];
	temp.data[7] = data[9];
	temp.data[8] = data[10];

	return mat3();
}

void mat4::Scale(const vec3 a)
{
	mat4 temp;
	temp.data[0] = a.x;
	temp.data[5] = a.y;
	temp.data[10] = a.z;
	*this = temp * *this;
	this->data[1] /= 1.5f;
	this->data[2] /= 2;
	this->data[4] *= 1.5f;
	this->data[6] /= 1.3333f;
	this->data[8] *= 2;
	this->data[9] *= 1.3333f;
	this->data[12] /= a.x;
	this->data[13] /= a.y;
	this->data[14] /= a.z;
}

void mat4::Scale(float scale)
{
	mat4 temp;
	temp.data[0] = scale;
	temp.data[5] = scale;
	temp.data[10] = scale;
	*this = temp * *this;
	this->data[12] /= scale;
	this->data[13] /= scale;
	this->data[14] /= scale;
}

void mat4::RotateX(float degrees)
{
	mat4 temp;
	float radians = degrees * (PI / 180.0f);
	temp.data[5] = static_cast<float>(cos(radians));
	temp.data[6] = static_cast<float>(sin(radians));
	temp.data[9] = static_cast<float>(-sin(radians));
	temp.data[10] = static_cast<float>(cos(radians));
	*this = temp * *this;
}

void mat4::RotateY(float degrees)
{
	mat4 temp;
	float radians = degrees * (PI / 180.0f);
	temp.data[0] = static_cast<float>(cos(radians));
	temp.data[2] = static_cast<float>(-sin(radians));
	temp.data[8] = static_cast<float>(sin(radians));
	temp.data[10] = static_cast<float>(cos(radians));
	*this = temp * *this;
}

void mat4::RotateZ(float degrees)
{
	mat4 temp;
	float radians = degrees * (PI / 180.0f);
	temp.data[0] = static_cast<float>(cos(radians));
	temp.data[1] = static_cast<float>(sin(radians));
	temp.data[4] = static_cast<float>(-sin(radians));
	temp.data[5] = static_cast<float>(cos(radians));
	*this = temp * *this;
}

void mat4::Translate(const vec3 a)
{
	mat4 temp;
	temp.data[12] = a.x;
	temp.data[13] = a.y;
	temp.data[14] = a.z;
	*this = temp * *this;
}

void mat4::LoadIdentity()
{
	data[0] = 1; data[4] = 0; data[8] = 0; data[12] = 0;
	data[1] = 0; data[5] = 1; data[9] = 0; data[13] = 0;
	data[2] = 0; data[6] = 0; data[10] = 1; data[14] = 0;
	data[3] = 0; data[7] = 0; data[11] = 0; data[15] = 1;
}

vec3 mat4::GetTranslation() const
{
	return vec3(data[12], data[13], data[14]);
}

mat4 mat4::PerspectiveProjection(float fov, float aspect, float zNear, float zFar)
{
	float yScale = 1.0f / static_cast<float>(tan((PI / 180.0f) * fov / 2));
	float xScale = yScale / aspect;
	mat4 temp(
		xScale, 0, 0, 0,
		0, yScale, 0, 0,
		0, 0, (zFar + zNear) / (zNear - zFar), 2 * zFar * zNear / (zNear - zFar),
		0, 0, -1, 0
	);
	return temp;
}

mat4 mat4::OrthographicProjection(float left, float right, float top, float bottom, float zNear, float zFar)
{
	mat4 temp(
		2 / (right - left), 0, 0, -(right + left) / (right - left),
		0, 2 / (top - bottom), 0, -(top + bottom) / (top - bottom),
		0, 0, -2 / (zFar - zNear), -(zFar + zNear) / (zFar - zNear),
		0, 0, 0, 1
	);
	return temp;
}

mat3 mat3::operator*(mat3 a) const
{
	mat3 temp;
	temp.data[0] = data[0] * a.data[0] + data[3] * a.data[1] + data[6] * a.data[2];
	temp.data[1] = data[1] * a.data[0] + data[4] * a.data[1] + data[7] * a.data[2];
	temp.data[2] = data[2] * a.data[0] + data[5] * a.data[1] + data[8] * a.data[2];

	temp.data[3] = data[0] * a.data[3] + data[3] * a.data[4] + data[6] * a.data[5];
	temp.data[4] = data[1] * a.data[3] + data[4] * a.data[4] + data[7] * a.data[5];
	temp.data[5] = data[2] * a.data[3] + data[5] * a.data[4] + data[8] * a.data[5];

	temp.data[6] = data[0] * a.data[6] + data[3] * a.data[7] + data[6] * a.data[8];
	temp.data[7] = data[1] * a.data[6] + data[4] * a.data[7] + data[7] * a.data[8];
	temp.data[8] = data[2] * a.data[6] + data[5] * a.data[7] + data[8] * a.data[8];
	return temp;
}

vec3 mat3::operator*(vec3 a) const
{
	vec3 temp;
	temp.x = data[0] * a.x + data[3] * a.y + data[6] * a.z;
	temp.y = data[1] * a.x + data[4] * a.y + data[7] * a.z;
	temp.z = data[2] * a.x + data[5] * a.y + data[8] * a.z;
	return temp;
}

mat3 mat3::operator*(float scalar) const
{
	mat3 temp;
	for (int i = 0; i < 9; i++)
	{
		temp.data[i] = data[i] * scalar;
	}
	return temp;
}

bool mat3::operator ==(mat3 a) const
{
	if (data[0] == a.data[0] && data[3] == a.data[3] && data[6] == a.data[6] &&
		data[1] == a.data[1] && data[4] == a.data[4] && data[7] == a.data[7] &&
		data[2] == a.data[2] && data[5] == a.data[5] && data[8] == a.data[8])
		return true;
	else
		return false;
}

bool mat3::operator !=(mat3 a) const
{
	if (data[0] != a.data[0] || data[3] != a.data[3] || data[6] != a.data[6] ||
		data[1] != a.data[1] || data[4] != a.data[4] || data[7] != a.data[7] ||
		data[2] != a.data[2] || data[5] != a.data[5] || data[8] != a.data[8])
		return true;
	else
		return false;
}