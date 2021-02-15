#pragma once

#include <litegfx.h>
#include <stb_image.h>
#include <glfw3.h>
#include <Collider.h>
#include "Vec2.h"

class Sprite {

public:
	float Blue = 1.0f, Green = 1.0f, Red = 1.0f, Alpha = 1.0f, Angle = 0.0f;
	lblend_t bMode = BLEND_ADD;
	int hFrames, vFrames;
	const ltex_t* BeeTexture;
	Vec2 NewTexturePosition, OldTexturePosition, Scale, Pivot;
	float InitialFrameSize = 0, FinalFrameSize = 1;
	int Frame = 0, Fps = 0;
	int fps = 60;
	int frameTime = 0.0;
	bool mustIncreaseScale;
	unsigned char* tempPixels = new unsigned char[500 * 500];
	//pixels array
	unsigned char* pixels;

	unsigned char* getPixels();
	//void setPixels(unsigned char* _pixels);


	//Pued ser un void y luego con un for iterar el array que le pasas por paramtero para luego cambiarle los valores
	//void pixelsAndPosition(int* solArray[], unsigned char* pixels, int xpos, int ypos, int textureWidth, int textureHight);

	// COLLISION	
	typedef enum {
		COLLISION_NONE,
		COLLISION_CIRCLE,
		COLLISION_RECT,
		COLLISION_PIXELS
	} CollisionType;

	CollisionType TCollision = COLLISION_NONE;
	const CircleCollider* CCollider;


	void setCollisionType(CollisionType type);
	CollisionType getCollisionType() const;
	const Collider* getCollider() const; 
	bool collides(const Sprite& other) const; 
	bool checkCollision(Sprite other);

	// Tpo de la funci�n callback
	typedef void (*CallbackFunc)(Sprite&, float);

	// Indicamos el n�mero de frames en horizontal y vertical
	// que tendr� la imagen del sprite
	Sprite(const ltex_t* tex, int hframes = 1, int vframes = 1);

	// Establecemos puntero a la funci�n callback
	void setCallback(CallbackFunc func);

	// Puntero gen�rico a datos (normalmente introducimos aqu� los datos
	// del sprite que se van a utilizar en la funci�n callback)
	void* getUserData();
	void setUserData(void* data);
	const ltex_t* getTexture() const; 
	static void setTexture(const ltex_t* tex, int hframes = 1, int vframes = 1);
	lblend_t getBlend() const;
	void setBlend(lblend_t mode);
	void setPixels(const ltex_t* tex);

	float getRed() const;
	float getGreen() const;
	float getBlue() const;
	float getAlpha() const;
	void setColor(float r, float g, float b, float a);
	const Vec2& getPosition() const;
	void setPosition(const Vec2& pos);
	float getAngle() const;
	void setAngle(float angle);
	const Vec2& getScale() const;
	void setScale(const Vec2& scale);

	// Tama�o de un frame multiplicado por la escala
	Vec2 getSize() const;

	// Este valor se pasa a ltex_drawrotsized en el pintado
	// para indicar el pivote de rotaci�n
	const Vec2& getPivot() const;
	void setPivot(const Vec2& pivot);
	int getHframes() const;
	int getVframes() const;

	// Veces por segundo que se cambia el frame de animaci�n
	int getFps() const;
	void setFps(int fps);

	// Frame actual de animaci�n
	float getCurrentFrame() const;
	void setCurrentFrame(int frame);
	void update(float deltaTime);
	void draw(float _xSize) const;
};