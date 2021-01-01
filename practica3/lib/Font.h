#pragma once


#include "Vec2.h"
#include "stb_truetype.h"
#include "glfw3.h"
#include "litegfx.h"

struct SColor {
	float r;
	float g;
	float b;
	float a;
};


class Font
{
private:
	static float height;
	Vec2 textSize;
	stbtt_bakedchar chardata[256];
	ltex_t* tex;


public:
	static Font* load(float height, Font* font, SColor randomColor);
	float getHeight() const;
	Vec2 getTextSize(const char* text) const;
	void draw(const char* text, const Vec2& pos) const;
	static void chargeInMemory(const char* filename);

public:

	Font();
	~Font();

};

