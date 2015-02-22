#include "vec3.h"
#include "vec4.h"

vec3::vec3()
{
	x = y = z = 0;
}

vec3::vec3(float a_x, float a_y, float a_z)
	: x(a_x), y(a_y), z(a_z)
{
}

vec3::vec3(float a_x, float a_y)
	: x(a_x), y(a_y), z(0)
{
}

vec3::vec3(vec3 &other)
	: x(other.x), y(other.y), z(other.z)
{
}

vec3::vec3(vec4 &other)
{
	x = other.x;
	y = other.y;
	z = other.z;
}

vec3& vec3::operator = (vec3& other)
{
	x = other.x;
	y = other.y;
	z = other.z;
	return *this;
}

float vec3::Magnitude()
{
	return sqrtf(x*x + y*y * z*z);
}

vec3 vec3::getNormalised()
{
	float Length = Magnitude();
	if (Length != 0)
		return vec3( x/ Length, y / Length, z / Length);
	else
		return *this;
}

float vec3::Dot(vec3 rhs)
{
	return x*x + y*y + z*z;
}

vec3 vec3::Cross(vec3 rhs)
{
	return vec3( y * rhs.z - z * rhs.y,
				 z * rhs.x - x * rhs.z,
				 x * rhs.y - y * rhs.x);
}

vec3 vec3::One()
{
	return vec3(1,1,1);
}

vec3 vec3::Zero()
{
	return vec3(0,0,0);
}

vec3 vec3::Lerp(vec3 Origin, vec3 Destination, float t)
{
	return Origin*(1-t) + Destination*t;
}

float vec3::Distance(vec3 Origin, vec3 Destination)
{
	return (Origin - Destination).Magnitude();
}

vec3 vec3::operator + (vec3 rhs)
{
	return vec3(x + rhs.x ,y + rhs.y, z + rhs.z );
}

vec3 vec3::operator - (vec3 rhs)
{
	return vec3(x - rhs.x ,y - rhs.y, z - rhs.z );
}

vec3 vec3::operator * (float scalar)
{
	return vec3(x*scalar, y * scalar, z * scalar);	
}

vec3 vec3::operator / (float scalar)
{
	return vec3(x/scalar, y/scalar, z/scalar);
}

vec3& vec3::operator += (vec3 rhs)
{
	*this = vec3(x + rhs.x, y + rhs.y, z + rhs.z);
	return *this;
}

vec3& vec3::operator -= (vec3 rhs)
{
	*this = vec3(x - rhs.x, y - rhs.y, z - rhs.z);
	return *this;
}

vec3& vec3::operator *= (float scalar)
{
	*this = vec3(x*scalar, y * scalar, z * scalar);	
	return *this;
}

vec3& vec3::operator /= (float scalar)
{
	*this = vec3(x/scalar, y / scalar, z / scalar);
	return *this;
}

bool vec3::operator == (vec3 rhs)
{
	return (x == rhs.x && y == rhs.y && z == rhs.z);
}

bool vec3::operator != (vec3 rhs)
{
	return !(x == rhs.x && y == rhs.y && z == rhs.z);
}

std::ostream& operator << (std::ostream& stream, const vec3& target)
{
	stream << "(" << target.x << ", " << target.y << ", " << target.z << ")";
	return stream;
}