#pragma once


#include <cmath>

class Vec2
{
private:
	float posX;
	float posY;


public:
	float getPosX() const { return this->posX; };
	float getPosY() const { return this->posY; };

	Vec2(float posX, float posY);
	Vec2();

	Vec2 getThisVector2D() { return Vec2(this->posX, this->posY); };

	Vec2 sumVec2(const Vec2& other);

	Vec2 diffVec2(const Vec2& other);
	Vec2 scaleVec2(const float num);
	Vec2 divVec2(const float num);
	float scalarProdVec2(const Vec2& other);
	Vec2 absVec2();
	float normVec2();
	float lenVec2();
	float angleVec2(const Vec2& other);
	float distanceVec2(const Vec2& other);

};

