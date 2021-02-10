#pragma once

#include <litegfx.h>
#include <stb_image.h>
#include <glfw3.h>
#include "Vec2.h"

class Sprite {

public:
	float Blue = 0.0f, Green = 0.0f, Red = 0.0f, Alpha = 0.0f, Angle = 0.0f;
	lblend_t blendMode = BLEND_ADD;

	int hFrames;
	int vFrames;

	const ltex_t* tex;

	Vec2 newPosition;
	Vec2 oldPosition; 

	Vec2 Scale;
	Vec2 Pivot;

	float iFrameSize = 0.f;
	float fFrameSize = 0.f;

	int Frame = 0;
	int Fps = 0;
	int fps = 60;
	int frameTime = 0.0;

	// frames en horizontal de la imagen y frames en vertical
	Sprite(const ltex_t* _tex, int _hFrames = 1, int _vFrames = 1);

	const ltex_t* getTexture() const; 
	static void setTexture(const ltex_t* _tex, int _hFrames = 1, int _vFrames = 1);

	//modo de filtrado
	lblend_t getBlend() const;
	void setBlend(lblend_t _mode);

	//color
	float getRed() const;
	float getGreen() const;
	float getBlue() const;
	float getAlpha() const;
	void setColor(float _r, float _g, float _b, float _a);

	//posición
	const Vec2& getPosition() const;
	void setPosition(const Vec2& _pos);

	//ángulo de rotación
	float getAngle() const;
	void setAngle(float _angle);

	//escala de la imagen
	const Vec2& getScale() const;
	void setScale(const Vec2& _scale);
	Vec2 getSize() const;

	//pivote donde se hace la rotación
	const Vec2& getPivot() const;
	void setPivot(const Vec2& _pivot);

	int getHFrames() const;
	int getVFrames() const;

	// frecuencia de refresco para cambiar de frame
	int getFps() const;
	void setFps(int fps);

	// frame actual que se ejecuta en la animación
	float getCurrentFrame() const;
	void setCurrentFrame(int _frame);
	void update(float _deltaTime);
	void draw() const;
};