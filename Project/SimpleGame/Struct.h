#pragma once

typedef struct Position {
	float fX;
	float fY;

	//������
	Position()
		: fX(0), fY(0)
	{}

	Position(float Xpos, float Ypos)
		: fX(Xpos), fY(Ypos)
	{}
}Pos;

typedef struct Size {
	float fX;
	float fY;
	float fZ;

	//������
	Size()
		: fX(0), fY(0), fZ(0)
	{}

	Size(float Xpos = 0, float Ypos = 0, float Zpos = 0)
		: fX(Xpos), fY(Ypos), fZ(Zpos)
	{}
}Siz;

typedef struct Color {
	float fR;
	float fG;
	float fB;
	float fAlpha;

	//������
	Color()
		: fR(0), fG(0), fB(0), fAlpha(0)
	{}

	Color(float fRed, float fGreen, float fBlue,float Alpha = 1)
		: fR(fRed), fG(fGreen), fB(fBlue), fAlpha(Alpha)
	{

	}
}RGBA;