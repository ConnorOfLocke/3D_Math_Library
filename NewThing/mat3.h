#ifndef _MAT3_H_
#define _MAT3_H_

#include <math.h>
#include "vec3.h"

class mat4;

class mat3
{
public:
	vec3 a;
	vec3 b;
	vec3 c;

	mat3();
	mat3(vec3 a_a, vec3 a_b, vec3 a_c);
	mat3(float a_ax, float a_ay, float a_az,
		 float a_bx, float a_by, float a_bz,
		 float a_cx, float a_cy, float a_cz);

	//mat3(mat4 other);

	mat3(mat3& other);
	mat3& operator = (mat3& other);

	mat3 getInverse();
	mat3 getTranspose();
	float getDeterminate();

	static mat3 getRotationXMatrix(float angle);
	static mat3 getRotationYMatrix(float angle);
	static mat3 getRotationZMatrix(float angle);

	static mat3 getScale(vec3 Scale);

	static mat3 Identity();
	static mat3 Zero();

	mat3 operator + (mat3 other);
	mat3 operator - (mat3 other);
	mat3 operator * (mat3 other);

	mat3 operator* (float scalar);
	mat3 operator/ (float scalar);

	mat3& operator += (mat3 other);
	mat3& operator -= (mat3 other);
	mat3& operator *= (mat3 other);

	mat3& operator *= (float scalar);
	mat3& operator /= (float scalar);

	bool operator == (mat3 other);
	bool operator != (mat3 other);

	friend std::ostream& operator << (std::ostream& stream, const mat3& target);
	float* ToArray();

};
#endif