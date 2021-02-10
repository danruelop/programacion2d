#include "Collider.h"
#include <iostream>

Vec2 collisionPositions[500 * 500];

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
	return false;
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
	printf("%f\n", pixelsSize.x);
	float farPosInX = rectPos.x >= pixelsPos.x ? rectPos.x : pixelsPos.x;
	float farPosInY = rectPos.y >= pixelsPos.y ? rectPos.y : pixelsPos.y;

	float closestFinalPointX = (rectPos.x + rectSize.x) <= (pixelsPos.x + pixelsSize.x) ? (rectPos.x + rectSize.x) : (pixelsPos.x + pixelsSize.x);
	float closestFinalPointY = (rectPos.y + rectSize.y) <= (pixelsPos.y + pixelsSize.y) ? (rectPos.y + rectSize.y) : (pixelsPos.y + pixelsSize.y);

	Vec2 cZonePos(farPosInX, farPosInY);
	Vec2 cZoneSize(abs(cZonePos.x - closestFinalPointX), abs(cZonePos.y - closestFinalPointY));

	int i = 0;
	int j = 0;
	
	Vec2 actualVector = Vec2();

	for(int z = 0; z < (cZoneSize.x * cZoneSize.y); z++)
	{
		actualVector.x = cZonePos.x + i;
		actualVector.y = cZonePos.y + j;
		collisionPositions[z] = actualVector;

		if(cZonePos.x + i > cZoneSize.x)
		{
			i = 0;
			j++;
		}
		i++;
	}

	Vec2 initialCZPixel(abs(pixelsPos.x - cZonePos.x), abs(pixelsPos.y - cZonePos.y));

	int i2 = 0;
	int j2 = 0;
	bool bColision = false;

	for (int cont = 0; cont < (cZoneSize.x * cZoneSize.y) && bColision == false; cont++)
	{
		int index = (((initialCZPixel.y + j2) * pixelsSize.x + (initialCZPixel.x + i2)) * 4) + 3;
		
	
		if (pixels[index] > 0)
		{ 
			printf("%i", pixels[index]);
			bColision = true; 
		}

		if(initialCZPixel.x + i2 >= cZoneSize.x)
		{
			i2 = 0;
			j2++;
		}
		cont++;
	}

	return bColision;
}

bool PixelCollider::checkPixelsPixels(const Vec2& pixelsPos1, const Vec2& pixelsSize1, unsigned char* pixels1, const Vec2& pixelsPos2, const Vec2& pixelsSize2, unsigned char* pixels2)
{
	return false;
}




