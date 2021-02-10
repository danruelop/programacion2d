#pragma once
#include "Vec2.h"

Vec2::Vec2() 
{
	v[0] = 0;
	v[1] = 0;
}

Vec2::Vec2(float x, float y)
{
	v[0] = x;
	v[1] = y;
}

Vec2 Vec2::Vec2Sum(const Vec2& vec) const
{
	Vec2 vc;
	vc.v[0] = v[0] + vec.v[0];
	vc.v[1] = v[1] + vec.v[1];
	return vc;
}

Vec2 Vec2::Vec2Sub(const Vec2& vec) const 
{
	Vec2 vc;
	vc.v[0] = v[0] - vec.v[0];
	vc.v[1] = v[1] - vec.v[1];
	return vc;
}

Vec2 Vec2::Vec2Prod(const Vec2& vec) const
{
	Vec2 vc;
	vc.v[0] = v[0] * vec.v[0];
	vc.v[1] = v[1] * vec.v[1];
	return vc;

}

Vec2 Vec2::Vec2Div(const Vec2& vec) const
{
	Vec2 vc;
	vc.v[0] = v[0] / vec.v[0];
	vc.v[1] = v[1] / vec.v[1];
	return vc;
}



Vec2 Vec2::ScalarSum(float num) const 
{
	Vec2 vc;
	vc.v[0] = v[0] + num;
	vc.v[1] = v[1] + num;
	return vc;
}

Vec2 Vec2::ScalarSub(float num) const
{

	Vec2 vc;
	vc.v[0] = v[0] - num;
	vc.v[1] = v[1] - num;
	return vc;
}

Vec2 Vec2::ScalarProd(float num) const
{
	Vec2 vc;
	vc.v[0] = v[0] * num;
	vc.v[1] = v[1] * num;
	return vc;
}

Vec2 Vec2::ScalarDiv(float num) const
{
	Vec2 vc;
	vc.v[0] = v[0] / num;
	vc.v[1] = v[1] / num;
	return vc;
}

float Vec2::Vec2Magnitude(const Vec2& vec) const
{
	return sqrtf(vec.x * vec.x + vec.y * vec.y);
}

Vec2 Vec2::NormalVec2(const Vec2& b)
{
	return Vec2(-b.y, b.x);
}

float Vec2::dot(const Vec2& a, const Vec2& b)
{
	return a.x * b.x + a.y * b.y;
}

float Vec2::angle(const Vec2& AngleVector) const 
{
	Vec2 vc = Vec2(this->x, this->y);
	float finalAngle = (float)((atan2(AngleVector.y - vc.y, AngleVector.x - vc.x)) * 180 / M_PI);
	if (finalAngle < 0) 
	{
		finalAngle += 360;
	}
	return finalAngle;
}

float Vec2::distance(const Vec2& other) const 
{
	Vec2 vc = Vec2(this->x, this->y);
	float distance = sqrtf((other.x-vc.x)*(other.x - vc.x) + (other.y - vc.y) * (other.y - vc.y));
	return distance;
}

