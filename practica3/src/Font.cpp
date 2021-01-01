
#define _CRT_SECURE_NO_WARNINGS

#include "litegfx.h"
#include <iostream>
#include "Font.h"

float Font::height = 0;

stbtt_aligned_quad* pRectInfo = new stbtt_aligned_quad();

unsigned char* fontBuffer;
unsigned char colorBuffer[512 * 512 * 4];
unsigned char* pColorBuffer = colorBuffer;

unsigned char bufferAlpha[512 * 512];
unsigned char* pBufferAlpha = bufferAlpha;

float* c_xpos = new float;
float* c_ypos = new float;

Font::Font()
{
}

Font::~Font()
{
}

void Font::chargeInMemory(const char* filename)
{
	
	long ttf_size;

	FILE* fontFile = fopen(filename, "r");

	fseek(fontFile, 0, SEEK_END);

	ttf_size = ftell(fontFile); /* how long is the file ? */

	fseek(fontFile, 0, SEEK_SET); /* reset */

	//data
	fontBuffer = (unsigned char*)malloc(ttf_size);

	fread(fontBuffer, ttf_size, 1, fontFile);

	fclose(fontFile);

}

Font* Font::load(float height, Font* font, SColor randomColor)
{
	int Error;

	font->height = height;

	//renderiza los caracteres pedidos en un buffer(solo componente alpha)
	Error = stbtt_BakeFontBitmap(
		//archivo ttf volcado en memoria
		fontBuffer,
		//0 para fuentes ttf
		0,
		//altura de la fuente
		height,
		//puntero donde se guardará el alpha buffer
		pBufferAlpha,
		//ancho del buffer anterior
		512,
		//altura del buffer anterior
		512,
		0, 255,
		font->chardata);

	;
	int counterBufferAlpha = 0;//1
	int j = 0;

	for (size_t i = 0; i < 512 * 512 * 4; i++)
	{
		if (i % 4 == 3)
		{
			pColorBuffer[i] = pBufferAlpha[counterBufferAlpha];
			counterBufferAlpha++;
		}
		
		else
		{	
			if(j == 0) 
			{
				pColorBuffer[i] = randomColor.r;
				j++;
			} else if(j == 1)
			{
				pColorBuffer[i] = randomColor.g;
				j++;
			}
			else 
			{
				pColorBuffer[i] = randomColor.b;
				j = 0;
			}
			
		}
	}

	font->tex = ltex_alloc(512, 512, 0);
	if (font->tex != nullptr)
	{
		ltex_setpixels(font->tex, pColorBuffer);
	}

	return font;	
}

float Font::getHeight() const
{
	return Font::height;
}

Vec2 Font::getTextSize(const char* text) const
{
	return Vec2();
}


void Font::draw(const char* text, const Vec2& pos) const
{
	*c_xpos = pos.getPosX();
	*c_ypos = pos.getPosY();

	for (size_t i = 0; i < strlen(text); i++) 
	{
		stbtt_GetBakedQuad(chardata,
			//ancho y alto de la fuente
			512, 512,
			text[i],
			c_xpos, c_ypos,
			pRectInfo,
			1);

		//lgfx_setcolor(randomColor.r, randomColor.g, randomColor.b, 255);

		ltex_drawrotsized(tex, *c_xpos, *c_ypos,
			0, 0.5, 0.5,
			pRectInfo->x1 - pRectInfo->x0, pRectInfo->y1 - pRectInfo->y0,
			pRectInfo->s0, pRectInfo->t0, pRectInfo->s1, pRectInfo->t1);

	}

}
