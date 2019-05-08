#pragma once
#include <math.h>

struct vec2 {
public:
	float x = 0;
	float y = 0;

	vec2() = default;
	vec2(float x1, float y1) { x = x1; y = y1; }
	explicit vec2(float a) { x = a; y = a; }

	vec2 operator*(float scalar) const;
	vec2 operator/(float divisor) const;
	vec2 operator*(vec2 a) const;
	vec2 operator/(vec2 a) const;
	vec2 operator+(vec2 a) const;
	vec2 operator-(vec2 a) const;

	vec2 operator*=(float scalar);
	vec2 operator/=(float divisor);
	vec2 operator*=(vec2 a);
	vec2 operator/=(vec2 a);
	vec2 operator+=(vec2 a);
	vec2 operator-=(vec2 a);

	bool operator ==(vec2 a) const;
	bool operator !=(vec2 a) const;
};

struct vec3 {
public:
	float x = 0;
	float y = 0;
	float z = 0;

	vec3() = default;
	vec3(float x1, float y1, float z1) { x = x1; y = y1; z = z1; }
	vec3(vec2 a, float z1) { x = a.x; y = a.y; z = z1; }
	explicit vec3(float a) { x = a; y = a; z = a; }

	vec3 operator*(float scalar) const;
	vec3 operator/(float divisor) const;
	vec3 operator*(vec3 a) const;
	vec3 operator/(vec3 a) const;
	vec3 operator+(vec3 a) const;
	vec3 operator-(vec3 a) const;

	vec3 operator*=(float scalar);
	vec3 operator/=(float divisor);
	vec3 operator*=(vec3 a);
	vec3 operator/=(vec3 a);
	vec3 operator+=(vec3 a);
	vec3 operator-=(vec3 a);

	bool operator ==(vec3 a) const;
	bool operator !=(vec3 a) const;

	void Normalize();
};

struct vec4 {
public:
	float x = 0;
	float y = 0;
	float z = 0;
	float w = 0;

	vec4() = default;
	vec4(float x1, float y1, float z1, float w1) { x = x1; y = y1; z = z1; w = w1; }
	vec4(vec2 a, float z1, float w1) { x = a.x; y = a.y; z = z1; w = w1; }
	vec4(vec3 a, float w1) { x = a.x; y = a.y; z = a.z; w = w1; }
	explicit vec4(float a) { x = a; y = a; z = a; w = a; }

	vec4 operator*(float scalar) const;
	vec4 operator/(float divisor) const;
	vec4 operator*(vec4 a) const;
	vec4 operator/(vec4 a) const;
	vec4 operator+(vec4 a) const;
	vec4 operator-(vec4 a) const;

	vec4 operator*=(float scalar);
	vec4 operator/=(float divisor);
	vec4 operator*=(vec4 a);
	vec4 operator/=(vec4 a);
	vec4 operator+=(vec4 a);
	vec4 operator-=(vec4 a);

	bool operator ==(vec4 a) const;
	bool operator !=(vec4 a) const;
};

float lerp(float p1, float p2, float interp);
vec2 lerp2(vec2 p1, vec2 p2, float interp);
vec3 lerp3(vec3 p1, vec3 p2, float interp);
vec4 lerp4(vec4 p1, vec4 p2, float interp);

float RandomRangef(float a, float b);