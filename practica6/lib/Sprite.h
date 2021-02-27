#pragma once

#include <litegfx.h>
#include <stb_image.h>
#include <glfw3.h>
#include <Collider.h>
#include "Vec2.h"

enum EIdleState 
{
	IDLE,
	LEFT,
	RIGHT
};

enum ESpriteType 
{
	SINGULAR,
	FULLBACKGROUND,
	HORIZONTALBACKGROUND,
};

class Sprite {



//variables
public:
	
	// COLLISION	
	typedef enum {
		COLLISION_NONE,
		COLLISION_CIRCLE,
		COLLISION_RECT,
		COLLISION_PIXELS
	} CollisionType;

	const ltex_t* texture;

	ESpriteType spriteType;
	char* spriteName;

	//RGBA
	float Blue = 1.0f;
	float Green = 1.0f; 
	float Red = 1.0f; 
	float Alpha = 1.0f; 
	float Angle = 0.0f;

	//BLEND MODE
	lblend_t bMode = BLEND_ADD;

	Vec2 NewTexturePosition;
	Vec2 OldTexturePosition; 
	Vec2 Scale; 
	Vec2 Pivot;
	
	//Frames

	int hFrames;
	int vFrames;
	float InitialFrameSize = 0;
	float FinalFrameSize = 1;
	int Frame = 0;
	int Fps = 0;
	int fps = 60;
	int frameTime = 0.0;
	bool mustIncreaseScale;
	unsigned char* tempPixels = new unsigned char[500 * 500];

	//pixels array
	unsigned char* pixels;
	EIdleState spriteIdleState = EIdleState::IDLE;
	float scrollRatio = 1.0f;

	//Funciones

public:

	Sprite(const ltex_t* tex, int hframes = 1, int vframes = 1);
	~Sprite();

	char* getSpriteName() { return spriteName; }
	void setSpriteName(char* _newSpriteName);

	const ltex_t* getTexture() const { return texture; }
	static void setTexture(const ltex_t* tex, int hframes = 1, int vframes = 1);

	ESpriteType getSpriteType() { return spriteType; }
	void setSpriteType(ESpriteType _newSpriteType);

	float getRed() const { return Red; }
	float getGreen() const { return Green; }
	float getBlue() const { return Blue; }
	float getAlpha() const { return Alpha; }
	void setColor(float r, float g, float b, float a);

	float getAngle() const { return Angle; }
	void setAngle(float angle);

	lblend_t getBlend() const { return bMode; }
	void setBlend(lblend_t mode);

	const Vec2& getPosition() const { return NewTexturePosition; }
	void setPosition(const Vec2& pos);

	const Vec2& getScale() const { return Scale; }
	void setScale(const Vec2& scale);
	const Vec2& getPivot() const { return Pivot; }
	void setPivot(const Vec2& pivot);
	Vec2 getSize() const;

	int getHframes() const { return hFrames; }
	int getVframes() const { return vFrames; }

	int getFps() const { return Fps; }
	void setFps(int fps);

	float getCurrentFrame() const;
	void setCurrentFrame(int frame);
	void update(float deltaTime);

	void draw(float _xSize) const;

	unsigned char* getPixels() { return pixels; }
	void setPixels(const ltex_t* tex);

	float getScrollRatio() { return scrollRatio; }
	void setScrollRatio(float _newScrollRatio);

	EIdleState getIdleState() { return spriteIdleState; }
	void setIdleState(EIdleState _newIdleState);

	typedef void (*CallbackFunc)(Sprite&, float);

	void setCallback(CallbackFunc func);

	void* getUserData();
	void setUserData(void* data);
	
	void setupSprite(char* _spriteName, ESpriteType _spriteType, Vec2 _scale, Vec2 _pivot, float _Fps, float _angle,
		lblend_t _Bmode, CollisionType _collisionType, float _scrollRatio);

	CollisionType TCollision = COLLISION_NONE;
	const CircleCollider* CCollider;


	void setCollisionType(CollisionType type);
	CollisionType getCollisionType() const;
	const Collider* getCollider() const; 
	bool collides(const Sprite& other) const; 
	bool checkCollision(Sprite other);


	
};