#include "vec4.h"
#include "vec3.h"


vec4::vec4()
{
	x = y = z = 0;
}

vec4::vec4(float a_x, float a_y, float a_z, float a_w)
	: x(a_x), y(a_y), z(a_z), w(a_w)
{
}

vec4::vec4(float a_x, float a_y, float a_z)
	: x(a_x), y(a_y), z(a_z), w(0)
{
}

vec4::vec4(vec3 a_v, float a_w)
{
	x = a_v.x;
	y = a_v.y;
	z = a_v.z;
	w = a_w;
}


vec4::vec4(vec3& other)
{
	x = other.x;
	y = other.y;
	z = other.z;
	w = 0;
}

vec4::vec4(vec4 &other)
{
	x = other.x;
	y = other.y;
	z = other.z;
	w = other.w;
}

vec4& vec4::operator=(vec4 &other)
{
	x = other.x;
	y = other.y;
	z = other.z;
	w = other.w;
	return *this;
}

float vec4::Magnitude()
{
	return sqrtf(x*x + y*y + z*z + w*w);
}

vec4 vec4::getNormalised()
{
	float Length = Magnitude();
	if (Length != 0)
		return vec4( x / Length, y / Length, z / Length, w / Length);
	else
		return *this;
}

float vec4::Dot(vec4 rhs)
{
	return x * rhs.x + y * rhs.y + z * rhs.z + w * rhs.w;
}

vec4 vec4::Lerp(vec4 Origin, vec4 Destination, float t)
{
	return Origin * (1-t) + Destination * t;
}

float vec4::Distance(vec4 Origin, vec4 Destination)
{
	return (Origin - Destination).Magnitude();
}

vec4 vec4::One()
{
	return vec4(1,1,1,1);
}

vec4 vec4::Zero()
{
	return vec4(0,0,0,0);
}

vec4 vec4::operator + (vec4 rhs)
{
	return vec4(x + rhs.x, y + rhs.y, z + rhs.z, w + rhs.w);
}

vec4 vec4::operator - (vec4 rhs)
{
	return vec4(x - rhs.x, y - rhs.y, z - rhs.z, w - rhs.w);
}

vec4 vec4::operator * (float scalar)
{
	return vec4(x * scalar, y * scalar, z * scalar, w * scalar);
}

vec4 vec4::operator / (float scalar)
{
	return vec4(x / scalar, y / scalar, z / scalar, w / scalar);
}

vec4& vec4::operator += (vec4 rhs)
{
	*this = vec4(x + rhs.x, y + rhs.y, z + rhs.z, w + rhs.w);
	return *this;
}

vec4& vec4::operator -= (vec4 rhs)
{
	*this = vec4(x - rhs.x, y - rhs.y, z - rhs.z, w - rhs.w);
	return *this;
}

vec4& vec4::operator *= (float scalar)
{
	*this = vec4(x * scalar, y * scalar, z * scalar, w * scalar);
	return *this;
}

vec4& vec4::operator /= (float scalar)
{
	*this = vec4(x / scalar, y / scalar, z / scalar, w / scalar);
	return *this;
}

bool vec4::operator == (vec4 rhs)
{
	return (x == rhs.x && y == rhs.y && z == rhs.z && w == rhs.w);
}

bool vec4::operator != (vec4 rhs)
{
	return !(x == rhs.x && y == rhs.y && z == rhs.z && w == rhs.w);
}

std::ostream& operator << (std::ostream& stream, const vec4& target)
{
	stream << "(" << target.x << ", " << target.y << ", " << target.z << ", " << target.w << ")";
	return stream;
}
