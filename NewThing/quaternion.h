#ifndef _QUATERNION_H_
#define _QUATERNION_H_

#include "vec3.h"
#include "vec4.h"

class quaternion
{
public:
	float w;
	vec3 v;

	quaternion();
	quaternion( vec3& axis, float theta);

	quaternion GetInverted();
	void Invert();

	quaternion operator * (quaternion& a_q);
	vec3 operator * (vec3& a_v);
};



#endif