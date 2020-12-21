#define LITE_GFX_IMPLEMENTATION
#define STB_IMAGE_IMPLEMENTATION
#define STB_TRUETYPE_IMPLEMENTATION

#include <litegfx.h>
#include <glfw3.h>
#include <iostream>
#include "Font.h"
#include <stb_image.h>
#include "stb_truetype.h"

long ttf_size;
unsigned char* fontBuffer;
unsigned char* pPixels_alphaBuffer;
unsigned char* pPixels_colorBuffer;

int sizeOfABuffer = sizeof(pPixels_alphaBuffer);
int* pSizeOfABuffer = &sizeOfABuffer;

//stbtt_bakedchar chardata;
stbtt_bakedchar* chardata;

int alphaBuffer;
int colorBuffer;

int* pBufferN;
int* pTextureWidth;
int* pTextureHeight;

stbtt_aligned_quad* pRBackground;


Font::Font()
{
};

Font::~Font()
{
};

ltex_t* loadTexture(const char* filename, int* i_width, int* i_height) {

	ltex_t* tex;
	//unsigned char* arrayBytes;
	//arrayBytes = stbi_load(filename, i_width, i_height, pBufferN, 4);

	int tempX = *i_width;
	int tempY = *i_height;

	if (pPixels_alphaBuffer != nullptr)
	{
		tex = ltex_alloc(tempX, tempY, 0);
		if (tex != nullptr)
		{
			ltex_setpixels(tex, pPixels_alphaBuffer);
		}
	}
	else {
		tex = nullptr;
	}
	return tex;
}

Font* Font::load(const char* filename, float height) 
{
	Font::height = height;

	FILE* fontFile = fopen(filename, "rb");

	fseek(fontFile, 0, SEEK_END);

	ttf_size = ftell(fontFile); /* how long is the file ? */

	fseek(fontFile, 0, SEEK_SET); /* reset */

	//data
	fontBuffer = (stbi_uc*)malloc(ttf_size);

	fread(fontBuffer, ttf_size, 1, fontFile);

	fclose(fontFile);

	//renderiza los caracteres pedidos en un buffer(solo componente alpha)
	alphaBuffer = stbtt_BakeFontBitmap(
		//archivo ttf volcado en memoria
		fontBuffer,
		//0 para fuentes ttf
		0, 
		//altura de la fuente
		height,
		//puntero donde se guardará el alpha buffer
		pPixels_alphaBuffer,
		//ancho del buffer anterior
		sizeof(pPixels_alphaBuffer),
		//altura del buffer anterior
		sizeof(pPixels_alphaBuffer),
		97, 77,
		chardata);

	

	//renderizar color buffer
	colorBuffer = stbtt_BakeFontBitmap(
		//archivo ttf volcado en memoria
		fontBuffer,
		//0 para fuentes ttf
		0,
		//altura de la fuente
		height,
		//puntero donde se guardará el color buffer
		pPixels_colorBuffer,
		//ancho del buffer anterior
		sizeof(pPixels_alphaBuffer) *4,
		//altura del buffer anterior
		sizeof(pPixels_alphaBuffer) *4,
		97, 77,
		chardata);

	int* pAlphaBuffer = &alphaBuffer;
	int* pColorBuffer = &alphaBuffer;

	loadTexture(filename, pTextureWidth, pTextureHeight);
	delete pAlphaBuffer;
	delete pColorBuffer;

	int tempTW = *pTextureWidth;
	int tempTH = *pTextureHeight;

	
	stbtt_GetBakedQuad(chardata, tempTW, tempTH, *pRBackground,
		float* xpos, float* ypos, pRBackground, 1);



	return nullptr;
}

float Font::getHeight() const
{
	return Font::height;
}

Vec2 Font::getTextSize(const char* text) const
{

}

void Font::draw(const char* text, const Vec2& pos) const
{

}
