#include "CPrintedText.h"


CPrintedText::CPrintedText(){}
CPrintedText::CPrintedText(Font* font, float posX, float posY, const char* selectedFont, unsigned int speed, SColor randomColor, const char* textToPrint)
{
	this->font = font;
	this->posX = posX;
	this->posY = posY;

	this->selectedFont = selectedFont;
	this->speed = speed;
	this->randomColor = randomColor;
	this->textToPrint = textToPrint;
	

}

CPrintedText::~CPrintedText() {}

void CPrintedText::setPosX(float newPosX)
{
	this->posX = newPosX;
}

void CPrintedText::printText()
{
	this->font->chargeInMemory(this->selectedFont);
	this->font->load(40, this->font, this->randomColor);
	this->font->draw(this->textToPrint, getPosVector());
}

Vec2 CPrintedText::getPosVector()
{
	return Vec2(this->posX, this->posY);
}