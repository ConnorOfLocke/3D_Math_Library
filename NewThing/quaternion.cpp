#include "quaternion.h"

quaternion::quaternion()
{
	w = 0;
	v = vec3();
}

quaternion::quaternion( vec3& axis, float theta)
{
	w = cosf(theta/2);
	v = axis * sinf(theta/2);
}

quaternion quaternion::GetInverted()
{
	quaternion q;
	q.w = w;
	q.v = v * (-1.0f);
	return q;
}

void quaternion::Invert()
{
	*this = GetInverted();
}

quaternion quaternion::operator * (quaternion& a_q)
{
	quaternion returnQ;
	returnQ.w = w*a_q.w - v.Dot(a_q.v);

	returnQ.v = v * a_q.w + a_q.v * w + v.Cross(a_q.v);

	return returnQ;
}

vec3 quaternion::operator * (vec3& a_v)
{
	quaternion pointQ;
	pointQ.w = 0;
	pointQ.v = a_v;

	vec3 vcV = v.Cross(a_v);
	return a_v + vcV * (2*w) + v.Cross(vcV) * 2;
}