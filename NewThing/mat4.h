#ifndef _MAT4_H_
#define _MAT4_H_

#include <math.h>
#include "vec4.h"
#include "vec3.h"

class mat3;

class mat4
{
public:
	vec4 a;
	vec4 b;
	vec4 c;
	vec4 d;

	mat4();

	mat4(vec4 a_a, vec4 a_b, vec4 a_c, vec4 a_d);

	mat4(float a_ax, float a_ay, float a_az, float a_aw,
		 float a_bx, float a_by, float a_bz, float a_bw,
		 float a_cx, float a_cy, float a_cz, float a_cw,
		 float a_dx, float a_dy, float a_dz, float a_dw);

	mat4(mat3 other);

	mat4(mat4& other);
	mat4& operator = (mat4& other);

	mat4 getInverse();
	mat4 getTranspose();
	float getDeterminate();

	static mat4 getRotationXMatrix(float angle);
	static mat4 getRotationYMatrix(float angle);
	static mat4 getRotationZMatrix(float angle);

	static mat4 getOrthographic(float left, float right, float bottom, float top, float near, float far);

	static mat4 getScale(vec3 Scale);
	static mat4 getTranslation(vec3 Position);

	static mat4 Identity();
	static mat4 Zero();

	mat4 operator + (mat4 other);
	mat4 operator - (mat4 other);
	mat4 operator * (mat4 other);

	mat4 operator * (float scalar);
	mat4 operator / (float scalar);

	mat4& operator += (mat4 other);
	mat4& operator -= (mat4 other);
	mat4& operator *= (mat4 other);

	mat4& operator *= (float scalar);
	mat4& operator /= (float scalar);

	bool operator == (mat4 other);
	bool operator != (mat4 other);

	friend std::ostream& operator << (std::ostream& stream, const mat4& target);
	float* ToArray();
};

#endif