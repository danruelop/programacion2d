#pragma once

#include "Font.h"




class CPrintedText
{

public:
	Font* font;

	float posX;
	float posY;

	const char* selectedFont;
	unsigned int speed;
	SColor randomColor;
	const char* textToPrint;
	
public:

	void setPosX(float newPosX);
	void printText();
	Vec2 getPosVector();

public:

	CPrintedText();
	CPrintedText(Font* font,float posX, float posY, const char* selectedFont, unsigned int speed, SColor randomColor, const char* textToPrint);
	~CPrintedText();

};