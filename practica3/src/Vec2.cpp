
#define _USE_MATH_DEFINES
#include <iostream>
#include <cmath>
#include "Vec2.h"
#include <math.h>



Vec2::Vec2(float pos_x, float pos_y)
{
	this->posX = pos_x;
	this->posY = pos_y;

}
Vec2::Vec2()
{
}
;


//A + B
Vec2 Vec2::sumVec2(const Vec2& other)
{
	float sX = Vec2::getPosX() + other.posX;
	float sY = Vec2::getPosY() + other.posY;
	return Vec2(sX, sY);
}
;

//A - B
Vec2 Vec2::diffVec2(const Vec2& other)
{
	float sX = Vec2::getPosX() - other.posX;
	float sY = Vec2::getPosY() - other.posY;
	return Vec2(sX, sY);
}
;

// Vector * Scalar
Vec2 Vec2::scaleVec2(const float num)
{
	float sX = Vec2::getPosX() * num;
	float sY = Vec2::getPosY() * num;
	return Vec2(sX, sY);
}
;

// Vector / Scalar
Vec2 Vec2::divVec2(const float num)
{
	float sX = Vec2::getPosX() / num;
	float sY = Vec2::getPosY() / num;
	return Vec2(sX, sY);
}
;

// Dot Product / Scalar Product
float Vec2::scalarProdVec2(const Vec2& other)
{
	return (Vec2::getPosX() * other.posX) + (Vec2::getPosY() * other.posY);
};

Vec2 Vec2::absVec2()
{
	float aX;
	float aY;
	//string result = (time < 18) ? "Good day." : "Good evening.";
	aX = (Vec2::getPosX() < 0) ? -Vec2::getPosX() : Vec2::getPosX();
	aY = (Vec2::getPosY() < 0) ? -Vec2::getPosY() : Vec2::getPosY();
	return Vec2(aX, aY);
};
float Vec2::normVec2()
{
	double pow1 = pow(Vec2::getPosX(), 2);
	double pow2 = pow(Vec2::getPosY(), 2);
	float sol = sqrt(pow1 + pow2);

	return sol;
};

float Vec2::lenVec2()
{
	return Vec2::getThisVector2D().normVec2();
};

float Vec2::angleVec2(const Vec2& other)
{
	return atan2(other.posY - Vec2::getPosY(), other.posX - Vec2::getPosX()) * 360 / 6.28f;
};

float Vec2::distanceVec2(const Vec2& other)
{
	Vec2 diff = diffVec2(other);
	return diff.normVec2();
};