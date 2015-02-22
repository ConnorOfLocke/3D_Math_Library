#ifndef _VEC3_H_
#define _VEC3_H_

#include <math.h>
#include <iostream>

class vec4;

class vec3
{
public:
	float x;
	float y;
	float z;

	vec3();
	vec3(float a_x, float a_y, float a_z);
	vec3(float a_x, float a_y);

	vec3(vec4 &other);

	vec3(vec3 &other);

	vec3& operator = (vec3& other);

	float Magnitude();
	vec3 getNormalised();

	float Dot(vec3 rhs);
	vec3 Cross(vec3 rhs);

	static vec3 One();
	static vec3 Zero();
	static vec3 Lerp(vec3 Origin, vec3 Destination, float t);
	static float Distance(vec3 Origin, vec3 Destination);

		//operators
	vec3 operator + (vec3 rhs);
	vec3 operator - (vec3 rhs);
	vec3 operator * (float scalar);
	vec3 operator / (float scalar);

	vec3& operator += (vec3 rhs);
	vec3& operator -= (vec3 rhs);
	vec3& operator *= (float scalar);
	vec3& operator /= (float scalar);

	//equlaity operators
	bool operator == (vec3 rhs);
	bool operator != (vec3 rhs);

	friend std::ostream& operator << (std::ostream& stream, const vec3& target);

};

#endif
