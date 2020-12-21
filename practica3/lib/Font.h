#pragma once

#include <iostream>
#include "Vec2.h"

class Font
{
private:
	static float height;
	Vec2 textSize;

public:

	static Font* load(const char* filename, float height);
	float getHeight() const;
	Vec2 getTextSize(const char* text) const;
	void draw(const char* text, const Vec2& pos) const;

private:

	Font();
	~Font();

};

