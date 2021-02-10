#include "Collider.h"
#include <iostream>
#include "litegfx.h"


bool CircleCollider::checkCircleCircle(const Vec2& pos1, float radius1, const Vec2& pos2, float radius2) const
{
	float distance = pos1.distance(pos2);
	float radiusSum = radius1 + radius2;
	printf("distance: %f, radius Sum: %f \n", distance, radiusSum);
	if (radiusSum >= distance)
	{
		return true;
	}
	else 
	{
		return false;
	}
}

bool CircleCollider::checkCircleRect(const Vec2& circlePos, float circleRadius, const Vec2& rectPos, const Vec2& rectSize)
{
	float distX = std::abs(circlePos.x - rectPos.x);
	float distY = std::abs(circlePos.y - rectPos.y);
	printf("%f, %f, %f\n", distX, rectSize.x / 2, circleRadius);
	
	if (distX  > (rectSize.x / 2 + circleRadius))
	{ 
		return false; 
	}
	else if (distY > (rectSize.y / 2 + circleRadius))
	{
		return false; 
	}
	else if ((distX) <= (rectSize.x / 2))
	{
		return true;
	}
	else if (distY <= (rectSize.y / 2))
	{
		return true;
	}
	
	float dx = distX - rectSize.x / 2;
	float dy = distY - rectSize.y / 2;
	return (dx * dx + dy * dy <= (circleRadius * circleRadius));
}

bool CircleCollider::checkCirclePixels(const Vec2& circlePos, float circleRadius, const Vec2& pixelsPos, const Vec2& pixelsSize, const uint8_t* pixels)
{
	int circleSize = circleRadius * 2;

	float farPosInX = circlePos.x >= pixelsPos.x ? circlePos.x : pixelsPos.x;
	float farPosInY = circlePos.y >= pixelsPos.y ? circlePos.y : pixelsPos.y;

	float closestFinalPointX = (circlePos.x + circleSize) <= (pixelsPos.x + pixelsSize.x) ? (circlePos.x + circleSize) : (pixelsPos.x + pixelsSize.x);
	float closestFinalPointY = (circlePos.y + circleSize) <= (pixelsPos.y + pixelsSize.y) ? (circlePos.y + circleSize) : (pixelsPos.y + pixelsSize.y);

	Vec2 cZonePos(farPosInX, farPosInY);
	Vec2 cZoneSize(abs(cZonePos.x - closestFinalPointX), abs(cZonePos.y - closestFinalPointY));

	int i = 0;
	int j = 0;

	Vec2 globalPosition = Vec2();
	Vec2 localPosition = Vec2();

	bool bCollision = false;

	for (int z = 0; z < (cZoneSize.x * cZoneSize.y); z++)
	{
		//global position of actual colision point
		globalPosition.x = cZonePos.x + i;
		globalPosition.y = cZonePos.y + j;

		//local position of actual colision point (reference is PixelsSprite)
		localPosition.x = abs(globalPosition.x - pixelsPos.x);
		localPosition.y = abs(globalPosition.y - pixelsPos.y);

		int transformLocalToIndex = (localPosition.y * pixelsSize.x + localPosition.x) * 4 + 3;

		lgfx_setcolor(0, 1, 0, 1);

		int circleCenterX = circlePos.x + circleRadius;
		int circleCenterY = circlePos.y + circleRadius;

		Vec2 circleCenter(circleCenterX, circleCenterY);

		lgfx_drawpoint(circleCenterX, circleCenterY);

		float dist = circleCenter.distance(globalPosition);

		if (cZonePos.x + i > cZonePos.x + cZoneSize.x)
		{
			i = 0;
			j++;
		}
		i++;

		if (pixels[transformLocalToIndex] > 0 && 
			dist < circleRadius)
		{
			lgfx_drawpoint(globalPosition.x, globalPosition.y);
			bCollision = true;
		}
	}

	return bCollision;
}

bool CircleCollider::collides(const Collider& other) const
{
	return false;
}
bool CircleCollider::collides(const Vec2& circlePos, float circleRadius) const
{
	return false;
}
bool CircleCollider::collides(const Vec2& rectPos, const Vec2& rectSize) const
{
	return false;
}
bool CircleCollider::collides(const Vec2& pixelsPos, const Vec2& pixelsSize, const uint8_t* pixels) const
{
	return false;
}



bool RectCollider::collides(const Collider& other) const 
{ 
	return 0; 
}
bool RectCollider::collides(const Vec2& circlePos, float circleRadius) const 
{ 
	return 0; 
}
bool RectCollider::collides(const Vec2& rectPos, const Vec2& rectSize) const 
{ 
	return 0; 
}
bool RectCollider::collides(const Vec2& pixelsPos, const Vec2& pixelsSize, const uint8_t* pixels) const 
{
	return 0; 
}



bool RectCollider::checkRectRect(const Vec2& rectPos1, const Vec2& rectSize1, const Vec2& rectPos2, const Vec2& rectSize2)
{
	if (rectPos1.x < rectPos2.x + rectSize2.x && rectPos1.x + rectSize1.x > rectPos2.x && rectPos1.y < rectPos2.y + rectSize2.y && rectPos1.y + rectSize1.y > rectPos2.y)
	{
		printf("He tocado R-R");
		return true;
	}
	else 
	{
		return false;
	}
}

bool RectCollider::checkPixelsRect(const Vec2& pixelsPos, const Vec2& pixelsSize, unsigned char* pixels, const Vec2& rectPos, const Vec2& rectSize)
{
	
	float farPosInX = rectPos.x >= pixelsPos.x ? rectPos.x : pixelsPos.x;
	float farPosInY = rectPos.y >= pixelsPos.y ? rectPos.y : pixelsPos.y;

	float closestFinalPointX = (rectPos.x + rectSize.x) <= (pixelsPos.x + pixelsSize.x) ? (rectPos.x + rectSize.x) : (pixelsPos.x + pixelsSize.x);
	float closestFinalPointY = (rectPos.y + rectSize.y) <= (pixelsPos.y + pixelsSize.y) ? (rectPos.y + rectSize.y) : (pixelsPos.y + pixelsSize.y);

	Vec2 cZonePos(farPosInX, farPosInY);
	Vec2 cZoneSize(abs(cZonePos.x - closestFinalPointX), abs(cZonePos.y - closestFinalPointY));

	int i = 0;
	int j = 0;
	
	Vec2 globalPosition = Vec2();
	Vec2 localPosition = Vec2();

	bool bCollision = false;

	for(int z = 0; z < (cZoneSize.x * cZoneSize.y); z++)
	{
		//global position of actual colision point
		globalPosition.x = cZonePos.x + i;
		globalPosition.y = cZonePos.y + j;
		
		//local position of actual colision point (reference is PixelsSprite)
		localPosition.x = abs(globalPosition.x - pixelsPos.x);
		localPosition.y = abs(globalPosition.y - pixelsPos.y);

		int transformLocalToIndex = (localPosition.y * pixelsSize.x + localPosition.x) * 4 + 3;


		if(cZonePos.x + i > cZonePos.x + cZoneSize.x)
		{
			i = 0;
			j++;
		}
		i++;

		if (pixels[transformLocalToIndex] > 0)
		{
			lgfx_setcolor(0, 1, 0, 1);
			lgfx_drawpoint(globalPosition.x, globalPosition.y);
			bCollision = true;
		}
	}

	return bCollision;
}

bool PixelCollider::checkPixelsPixels(const Vec2& pixelsPos1, const Vec2& pixelsSize1, unsigned char* pixels1, const Vec2& pixelsPos2, const Vec2& pixelsSize2, unsigned char* pixels2)
{
	float farPosInX = pixelsPos1.x >= pixelsPos2.x ? pixelsPos1.x : pixelsPos2.x;
	float farPosInY = pixelsPos1.y >= pixelsPos2.y ? pixelsPos1.y : pixelsPos2.y;

	float closestFinalPointX = (pixelsPos1.x + pixelsSize1.x) <= (pixelsPos2.x + pixelsSize2.x) ? (pixelsPos1.x + pixelsSize1.x) : (pixelsPos2.x + pixelsSize2.x);
	float closestFinalPointY = (pixelsPos1.y + pixelsSize1.y) <= (pixelsPos2.y + pixelsSize2.y) ? (pixelsPos1.y + pixelsSize1.y) : (pixelsPos2.y + pixelsSize2.y);

	Vec2 cZonePos(farPosInX, farPosInY);
	Vec2 cZoneSize(abs(cZonePos.x - closestFinalPointX), abs(cZonePos.y - closestFinalPointY));

	int i = 0;
	int j = 0;

	Vec2 globalPosition = Vec2();
	Vec2 localPositionPixels1 = Vec2();
	Vec2 localPositionPixels2 = Vec2();

	bool bCollision = false;

	for (int z = 0; z < (cZoneSize.x * cZoneSize.y); z++)
	{
		//global position of actual colision point
		globalPosition.x = cZonePos.x + i;
		globalPosition.y = cZonePos.y + j;

		//local position of actual colision point (reference is PixelsSprite1)
		localPositionPixels1.x = abs(globalPosition.x - pixelsPos1.x);
		localPositionPixels1.y = abs(globalPosition.y - pixelsPos1.y);

		//local position of actual colision point (reference is PixelsSprite2)
		localPositionPixels2.x = abs(globalPosition.x - pixelsPos2.x);
		localPositionPixels2.y = abs(globalPosition.y - pixelsPos2.y);


		int transformLocalToIndexPixels1 = (localPositionPixels1.y * pixelsSize1.x + localPositionPixels1.x) * 4 + 3;
		int transformLocalToIndexPixels2 = (localPositionPixels2.y * pixelsSize2.x + localPositionPixels2.x) * 4 + 3;

		//int setpixelsIndex = (((initialCZPixel.y + j) * pixelsSize.x + (initialCZPixel.x + i)) * 4) + 3;

		if (cZonePos.x + i > cZonePos.x + cZoneSize.x)
		{
			i = 0;
			j++;
		}
		i++;

		if (pixels1[transformLocalToIndexPixels1] > 0 && pixels1[transformLocalToIndexPixels2] > 0)
		{
			lgfx_setcolor(0, 1, 0, 1);
			lgfx_drawpoint(globalPosition.x, globalPosition.y);
			bCollision = true;
		}
	}

	return bCollision;
}

bool PixelCollider::collides(const Collider& other) const
{
	return false;
}

bool PixelCollider::collides(const Vec2& circlePos, float circleRadius) const
{
	return false;
}

bool PixelCollider::collides(const Vec2& rectPos, const Vec2& rectSize) const
{
	return false;
}

bool PixelCollider::collides(const Vec2& pixelsPos, const Vec2& pixelsSize, const uint8_t* pixels) const
{
	return false;
}




