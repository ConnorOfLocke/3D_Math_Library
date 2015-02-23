#include "colour.h"


colour::colour()
	: r(1.0f), g(1.0f), b(1.0f), a(1.0f)
{
}

colour::colour(float a_r, float a_g, float a_b, float a_a)
{
	//intresting way of setting of clamping between 1 and 0
	if (a_r > 0.0f)
		r = (a_r > 1.0f) ? 1.0f: a_r;	
	else
		r = 0.0f;

	if (a_g > 0.0f)
		g = (a_g > 1.0f) ? 1.0f: a_g;	
	else
		g = 0.0f;

	if (a_b > 0.0f)
		b = (a_b > 1.0f) ? 1.0f: a_b;	
	else
		b = 0.0f;

	if (a_a > 0.0f)
		a = (a_a > 1.0f) ? 1.0f: a_a;	
	else
		a = 0.0f;
}

colour::colour(float a_r, float a_g, float a_b)
{
	//intresting way of setting of clamping between 1 and 0
	if (a_r > 0.0f)
		r = (a_r > 1.0f) ? 1.0f: a_r;	
	else
		r = 0.0f;

	if (a_g > 0.0f)
		g = (a_g > 1.0f) ? 1.0f: a_g;	
	else
		g = 0.0f;

	if (a_b > 0.0f)
		b = (a_b > 1.0f) ? 1.0f: a_b;	
	else
		b = 0.0f;

	a = 1.0f;
}

colour::colour(unsigned int a_r, unsigned int a_g, unsigned int a_b, unsigned int a_a)
{
	r = (a_r/255.0f < 1.0f) ? a_r/255.0f : 1.0f;
	g = (a_g/255.0f < 1.0f) ? a_g/255.0f : 1.0f;
	b = (a_b/255.0f < 1.0f) ? a_b/255.0f : 1.0f;
	a = (a_a/255.0f < 1.0f) ? a_a/255.0f : 1.0f;
}

colour::colour(unsigned int a_r, unsigned int a_g, unsigned int a_b)
{
	r = (a_r/255.0f < 1.0f) ? a_r/255.0f : 1.0f;
	g = (a_g/255.0f < 1.0f) ? a_g/255.0f : 1.0f;
	b = (a_b/255.0f < 1.0f) ? a_b/255.0f : 1.0f;
	a = 1.0f;
}

colour::colour(colour& other)
{
	r = other.a;
	g = other.g;
	b = other.b;
	a = other.a;
}

colour::colour(vec4& other)
{
	r = other.x;
	g = other.y;
	b = other.z;
	a = other.w;	
}

colour& colour::operator=(colour &other)
{
	r = other.r;
	g = other.g;
	b = other.b;
	a = other.a;
	return *this;
}

colour& colour::operator=(vec4 &other)
{
	r = other.x;
	g = other.y;
	b = other.z;
	a = other.w;
	return *this;
}

vec3 colour::getHSL()
{
	//going off http://www.easyrgb.com/index.php?X=MATH&H=18#text18

	float H,S,L;

	//gets the max and min values
	float minVal = r;
	float maxVal = r;
	if (g < minVal)
		minVal = g;
	if (g > maxVal)
		maxVal = g;
	
	if (b < minVal)
		minVal = b;
	if (b > maxVal)
		maxVal = b;

	int diffVal =(int)( maxVal - minVal);

	//LIGHTNESS
	L = ( maxVal + minVal ) / 2;

	if ( diffVal == 0 )  //This is a gray, no chroma...
		H = S = 0;
	else                                    
	{
		//SATURATION
		if ( L <= 127.5f )
			S = diffVal / ( maxVal + minVal);
		else
			S = diffVal / ( 2 - maxVal - minVal );

		float del_R = ( ( ( maxVal - r ) / 6.0f ) + ( maxVal / 2.0f ) ) / maxVal;
		float del_G = ( ( ( maxVal - g ) / 6.0f ) + ( maxVal / 2.0f ) ) / maxVal;
		float del_B = ( ( ( maxVal - b ) / 6.0f ) + ( maxVal / 2.0f ) ) / maxVal;

		if ( r == maxVal)
			H = del_B - del_G;
		else if ( g == maxVal )
			H = ( 1.0f / 3.0f ) + del_R - del_B;
		else if ( b == maxVal )
			H = ( 2.0f / 3.0f ) + del_G - del_R;

		if ( H < 0 )
			H += 1;
		if ( H > 1 )
			H -= 1;
	}
	return vec3(H,S,L);

	//L from 0 to 1

}

void colour::setHSL(float Hue, float Saturation, float Lightness)
{
	//Going from http://www.easyrgb.com/index.php?X=MATH&H=19#text19

	if ( Saturation == 0 )   //monochromatic
	{
		r = Lightness;                      
		g = Lightness;
		b = Lightness;
	}
	else
	{
		float Input1, Input2;
		if ( Lightness < 0.5 )
			Input2 = Lightness * ( 1 + Saturation );
		else
			Input2 = Lightness + Saturation - Saturation*Lightness;

		Input1 = 2 * Lightness - Input2;

		r = HueToRGB( Input1, Input2, Hue + ( 1.0f / 3.0f ) );
		g = HueToRGB( Input1, Input2, Hue );
		b = HueToRGB( Input1, Input2, Hue - ( 1.0f / 3.0f ) );

		int llmaa = 1;
	}
}

float colour::HueToRGB(float v1, float v2, float vH)
{
	if ( vH < 0 ) 
		vH += 1.0f;
	if ( vH > 1 ) 
		vH -= 1.0f;

	if ( vH < 1.0f/6.0f )
		return v1 + ( v2 - v1 ) * 6.0f * vH ;
	
	if (  vH < 1.0f/2.0f )
		return v2 ;

	if ( vH  < 2.0f/3.0f )
		return v1 + ( v2 - v1 ) * ( 2.0f / 3.0f - vH ) * 6.0f;
	
	return  v1;
}

float colour::Hue()
{
	return getHSL().x;
}
void colour::SetHue(float a_fHue)
{
	vec3 curHSL = getHSL();
	setHSL(a_fHue, curHSL.y, curHSL.z);
}
float colour::Saturation()
{
	return getHSL().y;
}
void  colour::SetSaturation(float a_fSaturation)
{
	vec3 curHSL = getHSL();
	setHSL(curHSL.x, a_fSaturation, curHSL.z);
}
float colour::Lightness()
{
	return getHSL().z;
}
void  colour::SetLightness(float a_fLightness)
{
	vec3 curHSL = getHSL();
	setHSL(curHSL.x, curHSL.y, a_fLightness);
}

colour colour::Lerp(colour Original, colour nextColour, float t)
{
	return Original*(t-1) + nextColour*t;
}

colour colour::Red()
{
	return colour(1.0f, 0.0f, 0.0f, 1.0f);
}
colour colour::Green()
{
	return colour(0.0f, 1.0f, 0.0f, 1.0f);
}
colour colour::Blue()
{
	return colour(0.0f, 0.0f, 1.0f, 1.0f);
}
colour colour::Magenta()
{
	return colour(1.0f, 0.0f, 1.0f, 1.0f);
}
colour colour::Cyan()
{
	return colour(0.0f, 1.0f, 1.0f, 1.0f);
}
colour colour::Yellow()
{
	return colour(1.0f, 1.0f, 0.0f, 1.0f);
}
colour colour::NiceYellow()
{
	return colour(1.0f, 0.92f, 0.016f, 1.0f);
}
colour colour::Black()
{
	return colour(0.0f, 0.0f, 0.0f, 1.0f);
}
colour colour::Grey()
{
	return colour(0.5f, 0.5f, 0.5f, 1.0f);
}
colour colour::White()
{
	return colour(1.0f, 1.0f, 1.0f, 1.0f);
}
colour colour::Transparent()
{
	return colour(1.0f, 1.0f, 1.0f, 0.5f);
}
colour colour::Clear()
{
	return colour(0.0f, 0.0f, 0.0f, 0.0f);
}

//operators
colour colour::operator + (colour rhs)
{
	return colour(r + rhs.r, g + rhs.g, b + rhs.b, a + rhs.a);
}
colour colour::operator - (colour rhs)
{
	return colour(r - rhs.r, g - rhs.g, b - rhs.b, a - rhs.a);
}
colour colour::operator + (vec4 rhs)
{
	return colour(r + rhs.x, g + rhs.y, b + rhs.z, a + rhs.w);
}
colour colour::operator - (vec4 rhs)
{
	return colour(r - rhs.x, g - rhs.y, b - rhs.z, a - rhs.w);
}
colour colour::operator * (float scalar)
{
	return colour(r *scalar, g *scalar, b *scalar, a * scalar);
}
colour colour::operator / (float scalar)
{
	return colour(r / scalar, g / scalar, b / scalar, a / scalar);
}

colour& colour::operator += (colour rhs)
{
	r = a + rhs.r;
	g = g + rhs.g;
	b = b + rhs.b;
	a = a + rhs.a;
	return *this;
}
colour& colour::operator -= (colour rhs)
{
	a = a - rhs.a;
	g = g - rhs.g;
	b = b - rhs.b;
	a = a - rhs.a;
	return *this;
}
colour& colour::operator += (vec4 rhs)
{
	a = a + rhs.x;
	g = g + rhs.y;
	b = b + rhs.z;
	a = a + rhs.w;
	return *this;
}
colour& colour::operator -= (vec4 rhs)
{
	a = a - rhs.x;
	g = g - rhs.y;
	b = b - rhs.z;
	a = a - rhs.w;
	return *this;
}
colour& colour::operator *= (float scalar)
{
	a = a * scalar;
	g = g * scalar;
	b = b * scalar;
	a = a * scalar;
	return *this;

}
colour& colour::operator /= (float scalar)
{
	a = a / scalar;
	g = g / scalar;
	b = b / scalar;
	a = a / scalar;
	return *this;
}

bool colour::operator == (colour rhs)
{
	return (r == rhs.r && g == rhs.g && b == rhs.b && a == rhs.a);
}
bool colour::operator != (colour rhs)
{
	return !(r == rhs.r && g == rhs.g && b == rhs.b && a == rhs.a);
}
	 
bool colour::operator == (vec4 rhs)
{
	return (r == rhs.x && g == rhs.y && b == rhs.z && a == rhs.w);
}
bool colour::operator != (vec4 rhs)
{
	return !(r == rhs.x && g == rhs.y && b == rhs.z && a == rhs.w);
}

std::ostream& operator << (std::ostream& stream, const colour& target)
{
	std::string returnString;

	unsigned int new_r = ((int)target.r * 255);
	unsigned int new_g = ((int)target.g * 255);
	unsigned int new_b = ((int)target.b * 255);
	unsigned int new_a = ((int)target.a * 255);

	stream << "Colour: 0x" << std::hex << new_r << std::hex << new_g << std::hex << new_b << std::hex << new_a;
	return stream;
}

float* colour::ToArray()
{
	float* returnArray = new float[4];
	returnArray[0] = r;
	returnArray[1] = g;
	returnArray[2] = b;
	returnArray[3] = a;

	return returnArray;
}