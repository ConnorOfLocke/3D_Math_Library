#ifndef _VEC4_H_
#define _VEC4_H_

#include <math.h>
#include <iostream>

class vec3;

class vec4
{
public:
	float x;
	float y;
	float z;
	float w;

	//contructors
	vec4();
	vec4(float a_x, float a_y, float a_z, float a_w);
	vec4(float a_x, float a_y, float a_z);
	vec4(vec3 a_v, float a_w);

	vec4(vec4& other);

	vec4(vec3& other);

	vec4& operator=(vec4 &other);

	float Magnitude();
	vec4 getNormalised();

	float Dot(vec4 rhs);

	static vec4 One();
	static vec4 Zero();
	static vec4 Lerp(vec4 Origin, vec4 Destination, float t);
	static float Distance(vec4 Origin, vec4 Destination);

	//operators
	vec4 vec4::operator + (vec4 rhs);
	vec4 vec4::operator - (vec4 rhs);
	vec4 vec4::operator * (float scalar);
	vec4 vec4::operator / (float scalar);

	vec4& vec4::operator += (vec4 rhs);
	vec4& vec4::operator -= (vec4 rhs);
	vec4& vec4::operator *= (float scalar);
	vec4& vec4::operator /= (float scalar);

	//equlaity operators
	bool operator == (vec4 rhs);
	bool operator != (vec4 rhs);

	friend std::ostream& operator << (std::ostream& stream, const vec4& target);
};


#endif