#ifndef _COLOUR_H_
#define _COLOUR_H_

#include <math.h>
#include "vec4.h"
#include "vec3.h"


class colour
{
public:
	float r;
	float g;
	float b;
	float a;

	//contructors
	colour();
	colour(float a_r, float a_g, float a_b, float a_a);
	colour(float a_r, float a_g, float a_b);
	colour(unsigned int a_r, unsigned int a_g, unsigned int a_b, unsigned int a_a);
	colour(unsigned int a_r, unsigned int a_g, unsigned int a_b);
	colour(colour& other);
	colour(vec4& other);

	colour& operator=(colour &other);
	colour& operator=(vec4 &other);

	vec3 getHSL();
	void setHSL(float Hue, float Saturation, float Lightness);


	float Hue();
	void SetHue(float a_fHue);
	float Saturation();
	void SetSaturation(float a_fSaturation);
	float Lightness();
	void SetLightness(float a_fLightness);

	static colour Lerp(colour Original, colour nextColour, float t);

	static colour Red();
	static colour Green();
	static colour Blue();
	static colour Magenta();
	static colour Cyan();
	static colour Yellow();
	static colour NiceYellow();

	static colour Black();
	static colour Grey();
	static colour White();
	static colour Transparent();
	static colour Clear();

	//operators
	colour operator + (colour rhs);
	colour operator - (colour rhs);
	colour operator + (vec4 rhs);
	colour operator - (vec4 rhs);
	colour operator * (float scalar);
	colour operator / (float scalar);

	colour& operator += (colour rhs);
	colour& operator -= (colour rhs);
	colour& operator += (vec4 rhs);
	colour& operator -= (vec4 rhs);
	colour& operator *= (float scalar);
	colour& operator /= (float scalar);

	//equlaity operators
	bool operator == (colour rhs);
	bool operator != (colour rhs);

	bool operator == (vec4 rhs);
	bool operator != (vec4 rhs);

	friend std::ostream& operator << (std::ostream& stream, const colour& target);
	float* ToArray();

private:
	//not sure exactly what this is but it saves me putting in 20 lines of superflous code
	float HueToRGB(float v1, float v2, float vH);
};



#endif