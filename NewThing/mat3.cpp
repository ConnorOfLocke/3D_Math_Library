#include "mat3.h"
#include "mat4.h"

mat3::mat3()
	: a(vec3(1, 0, 0)),
	  b(vec3(0, 1, 0)),
	  c(vec3(0, 0, 1))
{
}
mat3::mat3(vec3 a_a, vec3 a_b, vec3 a_c)
	: a(a_a), b(a_b), c(a_c)
{
}

mat3::mat3(float a_ax, float a_ay, float a_az,
		float a_bx, float a_by, float a_bz,
		float a_cx, float a_cy, float a_cz)
		: a(vec3(a_ax, a_ay, a_az)),
		  b(vec3(a_bx, a_by, a_bz)),
		  c(vec3(a_cx, a_cy, a_cz))
{
}

mat3::mat3(mat3& other)
	: a (other.a), b(other.b), c(other.c)
{
}

mat3& mat3::operator = (mat3& other)
{
	a = other.a;
	b = other.b;
	c = other.c;
	return *this;
}

mat3 mat3::getInverse()
{
	float Determinate = getDeterminate();
	
	if (Determinate == 0.0f)
		return mat3().Zero();

	mat3 returnMatrix = mat3((b.y * c.z - c.y * b.z), (a.z * c.y - c.z * a.y), (a.y * b.z - b.y * a.z),
							 (b.z * c.x - c.z * b.x), (a.x * c.z - c.x * a.z), (a.z * b.x - b.z * a.x),
							 (b.x * c.y - c.x * b.y), (a.y * c.x - c.y * a.x), (a.x * b.y - b.x * a.y));

	return returnMatrix * (1/Determinate);
}

mat3 mat3::getTranspose()
{
	return mat3(a.x, b.x, c.x,
				a.y, b.y, c.y,
				a.z, b.z, c.z);
}

float mat3::getDeterminate()
{
	return a.x *(b.y * c.z - b.z * c.y) - a.y*(b.x * c.z - b.z * c.x) + a.z*(b.x * c.y - b.y*c.x);
}


mat3 mat3::getRotationXMatrix(float angle)
{
	return mat3(1,	0,			 0,
				0,  cosf(angle), -sinf(angle),
				0,  sinf(angle),  cosf(angle));
}

mat3 mat3::getRotationYMatrix(float angle)
{
	return mat3(cosf(angle),  0, sinf(angle),
		        0,			  1, 0,
				-sinf(angle), 0, cosf(angle));
}

mat3 mat3::getRotationZMatrix(float angle)
{
	return mat3(cosf(angle), -sinf(angle),	0,
				sinf(angle), cosf(angle),	0,
				0,			 0,				1);
}

mat3 mat3::getScale(vec3 Scale)
{
	return (mat3(Scale.x, 0, 0,
				 0, Scale.y, 0,
				 0, 0, Scale.z));
}

mat3 mat3::Identity()
{
	return mat3(1,0,0,
				0,1,0,
				0,0,1);
}
mat3 mat3::Zero()
{
	return mat3(0,0,0,
				0,0,0,
				0,0,0);
}

mat3 mat3::operator + (mat3 other)
{
	return mat3(a + other.a,
				b + other.b,
				c + other.c);	
}

mat3 mat3::operator - (mat3 other)
{
	return mat3(a - other.a,
			b - other.b,
			c - other.c);	
}

mat3 mat3::operator * (mat3 other)
{
	//eeeeeeehhhhhhhhhh
	return mat3( a.x * other.a.x + a.y * other.b.x + a.z * other.c.x,		a.x * other.a.y + a.y * other.b.y + a.z * other.c.y,	 a.x * other.a.z + a.y * other.b.z + a.z * other.c.z ,
				 b.x * other.a.x + b.y * other.b.x + b.z * other.c.x,		b.x * other.a.y + b.y * other.b.y + b.z * other.c.y,	 b.x * other.a.z + b.y * other.b.z + b.z * other.c.z ,
				 c.x * other.a.x + c.y * other.b.x + c.z * other.c.x,	    c.x * other.a.y + c.y * other.b.y + c.z * other.c.y,	 c.x * other.a.z + c.y * other.b.z + c.z * other.c.z ) ;
}

mat3 mat3::operator* (float scalar)
{
	return mat3(a*scalar, b*scalar, c*scalar);
}

mat3 mat3::operator/ (float scalar)
{
	return mat3(a/scalar, b/scalar, c/scalar);
}

mat3& mat3::operator += (mat3 other)
{
	a += other.a;
	b += other.b;
	c += other.c;
	return *this;
}

mat3& mat3::operator -= (mat3 other)
{
	a -= other.a;
	b -= other.b;
	c -= other.c;
	return *this;
}

mat3& mat3::operator *= (mat3 other)
{
	*this = mat3( a.x * other.a.x + a.y * other.b.x + a.z * other.c.x,		a.x * other.a.y + a.y * other.b.y + a.z * other.c.y,	 a.x * other.a.z + a.y * other.b.z + a.z * other.c.z ,
				 b.x * other.a.x + b.y * other.b.x + b.z * other.c.x,		b.x * other.a.y + b.y * other.b.y + b.z * other.c.y,	 b.x * other.a.z + b.y * other.b.z + b.z * other.c.z ,
				 c.x * other.a.x + c.y * other.b.x + c.z * other.c.x,	    c.x * other.a.y + c.y * other.b.y + c.z * other.c.y,	 c.x * other.a.z + c.y * other.b.z + c.z * other.c.z );
	return *this;
}

bool mat3::operator == (mat3 other)
{
	return (a == other.a && b == other.b && c == other.c);
}
bool mat3::operator != (mat3 other)
{
	return !(a == other.a && b == other.b && c == other.c);
}

std::ostream& operator << (std::ostream& stream, const mat3& target)
{
	stream << "[ " << target.a << " ]\n[ " << target.b << " ]\n[ " << target.c << " ]";
	return stream;
}

float* mat3::ToArray()
{
	float* newArray = new float[9];
	
	newArray[0] = a.x;
	newArray[1] = a.y;
	newArray[2] = a.z;
	newArray[3] = b.x;
	newArray[4] = b.y;
	newArray[5] = b.z;
	newArray[6] = c.x;
	newArray[7] = c.y;
	newArray[8] = c.z;
	return newArray;
}
