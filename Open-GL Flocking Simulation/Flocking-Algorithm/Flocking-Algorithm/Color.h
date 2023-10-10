#ifndef _MYCOLOR_
#define _MYCOLOR_

class MyColor 
{
public:
	MyColor(GLfloat _r, GLfloat _g, GLfloat _b, string _name="")
	{ r=_r; g=_g; b=_b; name =_name; 
	}
	GLfloat r, g, b;
	string name;
};
#endif