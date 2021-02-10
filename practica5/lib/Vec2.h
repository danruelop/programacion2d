#ifndef OBJECT_H
#define OBJECT_H
#define _USE_MATH_DEFINES
#include <math.h>
// const used to convert degrees into radians
#define ONE_RAD_IN_DEG static_cast<float>(360.0 / ( 2.0 * M_PI )) 
#define ONE_DEG_IN_RAD static_cast<float>(( 2.0f * M_PI ) / 360.0) 

class Vec2
{

public: //De aquí en adelante los miembros son públicos a no ser que se exprese lo contrario

	Vec2();
	Vec2(float x, float y);

	void setPosX(float _newX) { x = _newX; }
	void setPosY(float _newY) { y = _newY; }

	union {
		float v[2];
		struct {
			float x, y;
		};
	};

	// Vector Vector Operations
	Vec2 Vec2Sum(const Vec2& b) const; 
	Vec2 Vec2Sub(const Vec2& b) const;
	Vec2 Vec2Prod(const Vec2& b) const;
	Vec2 Vec2Div(const Vec2& b) const;

	// Vector Scalar Operations
	Vec2 ScalarSum(float num) const;
	Vec2 ScalarSub(float num) const;
	Vec2 ScalarProd(float num) const;
	Vec2 ScalarDiv(float num) const;

	float dot(const Vec2& a, const Vec2& b);
	float angle(const Vec2& other) const;
	float distance(const Vec2& other) const;
	float Vec2Magnitude(const Vec2& b) const;
	Vec2 NormalVec2(const Vec2& b);


};
#endif
