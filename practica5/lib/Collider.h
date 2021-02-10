#pragma once
#include <stdint.h>
#include "Vec2.h"


class Collider {

public:
	virtual bool collides(const Collider& other) const = 0;
	virtual bool collides(const Vec2& circlePos, float circleRadius) const = 0;
	virtual bool collides(const Vec2& rectPos, const Vec2& rectSize) const = 0;
	virtual bool collides(const Vec2& pixelsPos, const Vec2& pixelsSize, const uint8_t* pixels) const = 0;

};

class CircleCollider : Collider 
{
public:
	bool checkCircleCircle(const Vec2& pos1, float radius1, const Vec2& pos2, float radius2) const;
	bool checkCircleRect(const Vec2& circlePos, float circleRadius, const Vec2& rectPos, const Vec2& rectSize);
	bool checkCirclePixels(const Vec2& circlePos, float circleRadius, const Vec2& pixelsPos, const Vec2& pixelsSize, const uint8_t* pixels);

	bool collides(const Collider& other) const;
	bool collides(const Vec2& circlePos, float circleRadius) const;
	bool collides(const Vec2& rectPos, const Vec2& rectSize) const;
	bool collides(const Vec2& pixelsPos, const Vec2& pixelsSize, const uint8_t* pixels) const;
};

class RectCollider : Collider
{
public:
	bool checkRectRect(const Vec2& rectPos1, const Vec2& rectSize1, const Vec2& rectPos2, const Vec2& rectSize2);
	bool checkPixelsRect(const Vec2& pixelsPos, const Vec2& pixelsSize, unsigned char* pixels, const Vec2& rectPos, const Vec2& rectSize);

	bool collides(const Collider& other) const;
	bool collides(const Vec2& circlePos, float circleRadius) const;
	bool collides(const Vec2& rectPos, const Vec2& rectSize) const;
	bool collides(const Vec2& pixelsPos, const Vec2& pixelsSize, const uint8_t* pixels) const;
};

class PixelCollider : Collider
{
public:
	bool checkPixelsPixels(const Vec2& pixelsPos1, const Vec2& pixelsSize1, unsigned char* pixels1, const Vec2& pixelsPos2, const Vec2& pixelsSize2, unsigned char* pixels2);
	bool collides(const Collider& other) const;
	bool collides(const Vec2& circlePos, float circleRadius) const;
	bool collides(const Vec2& rectPos, const Vec2& rectSize) const;
	bool collides(const Vec2& pixelsPos, const Vec2& pixelsSize, const uint8_t* pixels) const;
	
};