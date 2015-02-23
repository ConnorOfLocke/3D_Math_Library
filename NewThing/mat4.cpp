#include "mat4.h"
#include "mat3.h"

mat4::mat4()
	: a(vec4(1, 0, 0, 0)),
	  b(vec4(0, 1, 0, 0)),
	  c(vec4(0, 0, 1, 0)),
	  d(vec4(0, 0, 0, 1))
{
}

mat4::mat4(vec4 a_a, vec4 a_b, vec4 a_c, vec4 a_d)
	: a(a_a), 
	  b(a_b),
	  c(a_c),
	  d(a_d)
{
}

mat4::mat4(float a_ax, float a_ay, float a_az, float a_aw,
		float a_bx, float a_by, float a_bz, float a_bw,
		float a_cx, float a_cy, float a_cz, float a_cw,
		float a_dx, float a_dy, float a_dz, float a_dw)
	:a(vec4(a_ax, a_ay, a_az, a_aw)),
	 b(vec4(a_bx, a_by, a_bz, a_bw)),
	 c(vec4(a_cx, a_cy, a_cz, a_cw)),
	 d(vec4(a_dx, a_dy, a_dz, a_dw))
{
}

mat4::mat4(mat3 other)
{
	a = vec4(other.a);
	b = vec4(other.b);
	c = vec4(other.c);
	d = vec4(0,0,0,0);
}

mat4::mat4(mat4& other)
	: a(other.a),
	  b(other.b),
	  c(other.c),
	  d(other.d)
{
}

mat4& mat4::operator = (mat4& other)
{
	a = other.a;
	b = other.b;
	c = other.c;
	d = other.d;
	return *this;

}

mat4 mat4::getInverse()
{
	float Determinate = getDeterminate();
	if (Determinate == 0)
		return mat4().Zero();

	vec4 row1 = vec4( b.y*c.z*d.w + b.z*c.w*d.y + b.w*c.y*d.z - b.y*c.w*d.z - b.z*c.y*d.w - b.w*c.z*d.y,
					  a.y*c.w*d.z + a.z*c.y*d.w + a.w*c.z*d.y - a.y*c.z*d.w - a.z*c.w*d.y - a.w*c.y*d.z,
					  a.y*b.z*d.w + a.z*b.w*d.y + a.w*b.y*d.z - a.y*b.w*d.z - a.z*b.y*d.w - a.w*b.z*d.y,
					  a.y*b.w*c.z + a.z*b.y*c.w + a.w*b.z*c.y - a.y*b.z*c.w - a.z*b.w*c.y - a.w*b.y*c.z);

	vec4 row2 = vec4( b.x*c.w*d.z + b.z*c.x*d.w + b.w*c.z*d.x - b.x*c.z*d.w - b.z*c.w*d.x - b.w*c.x*d.z,
					  a.x*c.z*d.w + a.z*c.w*d.x + a.w*c.x*d.z - a.x*c.w*d.z - a.z*c.x*d.w - a.w*c.z*d.x,
					  a.x*b.w*d.z + a.z*b.x*d.w + a.w*b.z*d.x - a.x*b.z*d.w - a.z*b.w*d.x - a.w*b.x*d.z,
					  a.x*b.z*c.w + a.z*b.w*c.x + a.w*b.x*c.z - a.x*b.w*c.z - a.z*b.x*c.w - a.w*b.z*c.x);

	vec4 row3 = vec4( b.x*c.y*d.w + b.y*c.w*d.x + b.w*c.x*d.y - b.x*c.w*d.y - b.y*c.x*d.w - b.w*c.y*d.x,
					  a.x*c.w*d.y + a.y*c.x*d.w + a.w*c.y*d.x - a.x*c.y*d.w - a.y*c.w*d.x - a.w*c.x*d.y,
					  a.x*b.y*d.w + a.y*b.w*d.x + a.w*b.x*d.y - a.x*b.w*d.y - a.y*b.x*d.w - a.w*b.y*d.x,
					  a.x*b.w*c.y + a.y*b.x*c.w + a.w*b.y*c.x - a.x*b.y*c.w - a.y*b.w*c.x - a.w*b.x*c.y);

	vec4 row4 = vec4( b.x*c.z*d.y + b.y*c.x*d.z + b.z*c.y*d.x - b.x*c.y*d.z - b.y*c.z*d.x - b.z*c.x*d.y,
					  a.x*c.y*d.z + a.y*c.z*d.x + a.z*c.x*d.y - a.x*c.z*d.y - a.y*c.x*d.z - a.z*c.y*d.x,
					  a.x*b.z*d.y + a.y*b.x*d.z + a.z*b.y*d.x - a.x*b.y*d.z - a.y*b.z*d.x - a.z*b.x*d.y,
					  a.x*b.y*c.z + a.y*b.z*c.x + a.z*b.x*c.y - a.x*b.z*c.y - a.y*b.x*c.z - a.z*b.y*c.x);

	mat4 adjoin = mat4(row1, row2, row3, row4);

	return adjoin * (1/Determinate);
}

mat4 mat4::getTranspose()
{
	return mat4(a.x, b.x, c.x, d.x,
				a.y, b.y, c.y, d.y,
				a.z, b.z, c.z, d.z,
				a.w, b.w, c.w, d.w);
}

float mat4::getDeterminate()
{
	float D1 = a.x * mat3(  b.y, b.z, b.w,
							c.y, c.z, c.w,
							d.y, d.z, d.w).getDeterminate();

	float D2 = a.y * mat3(  b.x, b.z, b.w,
							c.x, c.z, c.w,
							d.x, d.z, d.w).getDeterminate();

	float D3 = a.z * mat3( b.x, b.y, b.w,
						   c.x, c.y, c.w,
						   d.x, d.y, d.w).getDeterminate();

	float D4 = a.w * mat3( b.x, b.y, b.z,
						   c.x, c.y, c.z,
						   d.x, d.y, d.z).getDeterminate();

	return D1 - D2 + D3 - D4;
}

mat4 mat4::getRotationXMatrix(float angle)
{
	mat4 returnMatrix = mat4(mat3().getRotationXMatrix(angle));
	returnMatrix.d.w = 1;
	return returnMatrix;
}

mat4 mat4::getRotationYMatrix(float angle)
{
	mat4 returnMatrix = mat4(mat3().getRotationYMatrix(angle));
	returnMatrix.d.w = 1;
	return returnMatrix;
}

mat4 mat4::getRotationZMatrix(float angle)
{
	mat4 returnMatrix = mat4(mat3().getRotationZMatrix(angle));
	returnMatrix.d.w = 1;
	return returnMatrix;
}

mat4 mat4::getOrthographic(float left, float right, float bottom, float top, float near, float far)
{
	if (right - left == 0 || top - bottom == 0 || far - near == 0)
		return mat4::Zero();

	return mat4( 2.0f/(right-left),			   0,							 0,								0,
				 0,								2.0f/(top-bottom),			 0,								0,
				 0,							   0,				 			 2.0f/(far - near),				0,
				 -((right + left)/(right-left)), -((top + bottom)/(top - bottom)), -((far + near)/(far - near)),	1 );


}	

mat4 mat4::getProjection(float fovy, float aspect, float zNear, float zFar)
{
	if (zNear * tanf(fovy / 2) == 0)
		return mat4::Zero();

	float S = 1.0f / ( zNear * tanf(fovy /2.0f));

	return mat4(aspect * S, 0,	0,								0,
				0,			S,	0,								0,
				0,			0,	-(zFar + zNear)/(zFar - zNear),	2*(zFar*zNear),
				0,			0,	-1,								0);
}

mat4 mat4::LookAt(vec3 from, vec3 to, vec3 up)
{
	vec3 zAxis = vec3::Normalize(from - to);
	vec3 xAxis = vec3::Normalize(up.Cross(zAxis));
	vec3 yAxis = vec3::Cross(zAxis, xAxis);

	return mat4(xAxis.x, xAxis.y, xAxis.z,  -vec3::Dot(xAxis, from),
				yAxis.x, yAxis.y, yAxis.z,	-vec3::Dot(yAxis, from),
				zAxis.x, zAxis.y, zAxis.z,	-vec3::Dot(zAxis, from),
				0,		 0,		  0,		1);
}

mat4 mat4::getScale(vec3 Scale)
{
	return mat4(Scale.x, 0.0f,	 0.0f,   0.0f,
				0.0f,	Scale.y, 0.0f,   0.0f,
				0.0f,	0.0f,	Scale.z, 0.0f,
				0.0f,  0.0f,	0.0f,	 1.0f);
}

mat4 mat4::getTranslation(vec3 Position)
{
	return mat4(1.0f, 0.0f, 0.0f, Position.x,
				0.0f, 1.0f, 0.0f, Position.y,
				0.0f, 0.0f,	1.0f, Position.z,
				0.0f, 0.0f,	0.0f, 1.0f);
}

mat4 mat4::Identity()
{
	return mat4(1.0f, 0.0f, 0.0f, 0.0f,
				0.0f, 1.0f, 0.0f, 0.0f,
				0.0f, 0.0f,	1.0f, 0.0f,
				0.0f, 0.0f,	0.0f, 1.0f);
}

mat4 mat4::Zero()
{
	return mat4(0.0f, 0.0f, 0.0f, 0.0f,
			0.0f, 0.0f, 0.0f, 0.0f,
			0.0f, 0.0f,	0.0f, 0.0f,
			0.0f, 0.0f,	0.0f, 0.0f);
}

mat4 mat4::operator + (mat4 other)
{
	return mat4(a + other.a,
				b + other.b,
				c + other.c,
				d + other.d);
}

mat4 mat4::operator - (mat4 other)
{
	return mat4(a - other.a,
				b - other.b,
				c - other.c,
				d - other.d);
}

mat4 mat4::operator * (mat4 other)
{
	vec4 row1 = vec4(a.x * other.a.x + a.y * other.b.x + a.z * other.c.x + a.w * other.d.x,
					 a.x * other.a.y + a.y * other.b.y + a.z * other.c.y + a.w * other.d.y,
					 a.x * other.a.z + a.y * other.b.z + a.z * other.c.z + a.w * other.d.z,
					 a.x * other.a.w + a.y * other.b.w + a.z * other.c.w + a.w * other.d.w);

	vec4 row2 = vec4(b.x * other.a.x + b.y * other.b.x + b.z * other.c.x + b.w * other.d.x,
					 b.x * other.a.y + b.y * other.b.y + b.z * other.c.y + b.w * other.d.y,
					 b.x * other.a.z + b.y * other.b.z + b.z * other.c.z + b.w * other.d.z,
					 b.x * other.a.w + b.y * other.b.w + b.z * other.c.w + b.w * other.d.w);
	
	vec4 row3 = vec4(c.x * other.a.x + c.y * other.b.x + c.z * other.c.x + c.w * other.d.x,
					 c.x * other.a.y + c.y * other.b.y + c.z * other.c.y + c.w * other.d.y,
					 c.x * other.a.z + c.y * other.b.z + c.z * other.c.z + c.w * other.d.z,
					 c.x * other.a.w + c.y * other.b.w + c.z * other.c.w + c.w * other.d.w);

	vec4 row4 = vec4(d.x * other.a.x + d.y * other.b.x + d.z * other.c.x + d.w * other.d.x,
					 d.x * other.a.y + d.y * other.b.y + d.z * other.c.y + d.w * other.d.y,
					 d.x * other.a.z + d.y * other.b.z + d.z * other.c.z + d.w * other.d.z,
					 d.x * other.a.w + d.y * other.b.w + d.z * other.c.w + d.w * other.d.w);


	return mat4( row1, row2, row3, row4 );
}

mat4 mat4::operator * (float scalar)
{
	return mat4(a * scalar,
				b * scalar,
				c * scalar,
				d * scalar);
}

mat4 mat4::operator / (float scalar)
{
	return mat4(a / scalar,
				b / scalar,
				c / scalar,
				d / scalar);
}

mat4& mat4::operator += (mat4 other)
{
	*this = mat4(a + other.a,
				b + other.b,
				c + other.c,
				d + other.d);
	return *this;
}

mat4& mat4::operator -= (mat4 other)
{
	*this = mat4(a - other.a,
				 b - other.b,
				 c - other.c,
				 d - other.d);
	return *this;
}

mat4& mat4::operator *= (mat4 other)
{
	vec4 row1 = vec4(a.x * other.a.x + a.y * other.b.x + a.z * other.c.x + a.w * other.d.x,
					 a.x * other.a.y + a.y * other.b.y + a.z * other.c.y + a.w * other.d.y,
					 a.x * other.a.z + a.y * other.b.z + a.z * other.c.z + a.w * other.d.z,
					 a.x * other.a.w + a.y * other.b.w + a.z * other.c.w + a.w * other.d.w);

	vec4 row2 = vec4(b.x * other.a.x + b.y * other.b.x + b.z * other.c.x + b.w * other.d.x,
					 b.x * other.a.y + b.y * other.b.y + b.z * other.c.y + b.w * other.d.y,
					 b.x * other.a.z + b.y * other.b.z + b.z * other.c.z + b.w * other.d.z,
					 b.x * other.a.w + b.y * other.b.w + b.z * other.c.w + b.w * other.d.w);
	
	vec4 row3 = vec4(c.x * other.a.x + c.y * other.b.x + c.z * other.c.x + c.w * other.d.x,
					 c.x * other.a.y + c.y * other.b.y + c.z * other.c.y + c.w * other.d.y,
					 c.x * other.a.z + c.y * other.b.z + c.z * other.c.z + c.w * other.d.z,
					 c.x * other.a.w + c.y * other.b.w + c.z * other.c.w + c.w * other.d.w);

	vec4 row4 = vec4(d.x * other.a.x + d.y * other.b.x + d.z * other.c.x + d.w * other.d.x,
					 d.x * other.a.y + d.y * other.b.y + d.z * other.c.y + d.w * other.d.y,
					 d.x * other.a.z + d.y * other.b.z + d.z * other.c.z + d.w * other.d.z,
					 d.x * other.a.w + d.y * other.b.w + d.z * other.c.w + d.w * other.d.w);

	*this = mat4( row1, row2, row3, row4 );
	return *this;
}

mat4& mat4::operator *= (float scalar)
{
	*this = mat4(a * scalar,
				b * scalar,
				c * scalar,
				d * scalar);
	return *this;
}

mat4& mat4::operator /= (float scalar)
{
	*this = mat4(a / scalar,
				 b / scalar,
				 c / scalar,
				 d / scalar);
	return *this;
}

bool mat4::operator == (mat4 other)
{
	return (a == other.a && b == other.b && c == other.c && d == other.d);
}

bool mat4::operator != (mat4 other)
{
	return !(a == other.a && b == other.b && c == other.c && d == other.d);
}

std::ostream& operator << (std::ostream& stream, const mat4& target)
{
	stream << "[" << target.a << "]\n[" << target.b << "]\n[" << target.c << "]\n[" << target.d << "]";
	return stream;
}

float* mat4::ToArray()
{
	float* newArray = new float[16];
	
	newArray[0] = a.x;
	newArray[1] = a.y;
	newArray[2] = a.z;
	newArray[3] = a.w;
	newArray[4] = b.x;
	newArray[5] = b.y;
	newArray[6] = b.z;
	newArray[7] = b.w;
	newArray[8] =  c.x;
	newArray[9] =  c.y;
	newArray[10] = c.z;
	newArray[11] = c.w;
	newArray[12] = d.x;
	newArray[13] = d.y;
	newArray[14] = d.z;
	newArray[15] = d.w;	
	return newArray;
}
