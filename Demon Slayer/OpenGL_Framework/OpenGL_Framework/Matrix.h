#pragma once
#include "Vector.h"

struct mat3
{

	mat3() {
		data[0] = 1; data[3] = 0; data[6] = 0;
		data[1] = 0; data[4] = 1; data[7] = 0;
		data[2] = 0; data[5] = 0; data[8] = 1;
	}
	mat3(float f0, float f3, float f6,
		float f1, float f4, float f7,
		float f2, float f5, float f8) {
		data[0] = f0; data[3] = f3; data[6] = f6;
		data[1] = f1; data[4] = f4; data[7] = f7;
		data[2] = f2; data[5] = f5; data[8] = f8;
	}

	mat3 operator*(mat3 a) const;
	vec3 operator*(vec3 a) const;
	mat3 operator*(float scalar) const;

	bool operator ==(mat3 a) const;
	bool operator !=(mat3 a) const;

	float data[9];
};

struct mat4
{

	mat4() {
		data[0] = 1; data[4] = 0; data[8] = 0; data[12] = 0;
		data[1] = 0; data[5] = 1; data[9] = 0; data[13] = 0;
		data[2] = 0; data[6] = 0; data[10] = 1; data[14] = 0;
		data[3] = 0; data[7] = 0; data[11] = 0; data[15] = 1;
	}
	mat4(float f0, float f4, float f8, float f12,
		float f1, float f5, float f9, float f13,
		float f2, float f6, float f10, float f14,
		float f3, float f7, float f11, float f15) {
		data[0] = f0; data[4] = f4; data[8] = f8; data[12] = f12;
		data[1] = f1; data[5] = f5; data[9] = f9; data[13] = f13;
		data[2] = f2; data[6] = f6; data[10] = f10; data[14] = f14;
		data[3] = f3; data[7] = f7; data[11] = f11; data[15] = f15;
	}

	mat4 operator*(mat4 a) const;
	vec4 operator*(vec4 a) const;
	mat4 operator*(float scalar) const;

	bool operator ==(mat4 a) const;
	bool operator !=(mat4 a) const;

	mat4 GetInverse() const;
	vec3 GetDirectionVec() const;
	mat3 GetRotationMat() const;

	void LoadIdentity();

	void Scale(const vec3 a);
	void Scale(float scale);

	void RotateX(float degrees);
	void RotateY(float degrees);
	void RotateZ(float degrees);

	void Translate(const vec3 a);

	vec3 GetTranslation() const;

	static mat4 PerspectiveProjection(float fov, float aspect, float zNear, float zFar);

	static mat4 OrthographicProjection(float left, float right, float top, float bottom, float zNear, float zFar);

	float data[16];
};