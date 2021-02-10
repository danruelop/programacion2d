#pragma once
#include "Sprite.h"
#include <string.h>


	
	// Indicamos el número de frames en horizontal y vertical
	// que tendrá la imagen del sprite
	Sprite::Sprite(const ltex_t* tex, int hframes, int vframes) 
	{
		
		BeeTexture = tex;
		hFrames = hframes;
		vFrames = vframes;

	}

	const ltex_t* Sprite::getTexture() const
	{
		return BeeTexture;
	}

	void Sprite::setTexture(const ltex_t* tex, int hframes, int vframes)
	{
		Sprite* newTexture = new Sprite(tex, hframes, vframes);
	}

	lblend_t Sprite::getBlend() const 
	{
		return bMode;
	}

	void Sprite::setBlend(lblend_t mode) 
	{
		bMode = mode;
		lgfx_setblend(bMode);
	}

	void Sprite::setPixels(const ltex_t* tex)
	{
		ltex_getpixels(tex, tempPixels);
		for (int i = 0; i < 500; i++) 
		{
			printf("%d", tempPixels[i]);
		}

		pixels = tempPixels;
		
	}

	unsigned char* Sprite::getPixels() 
	{
		return pixels;
	}

	// COLOR
	float Sprite::getRed() const
	{
		return Red;
	}

	float Sprite::getGreen() const
	{
		return Green;
	}

	float Sprite::getBlue() const
	{
		return Blue;
	}

	float Sprite::getAlpha() const
	{
		return Alpha;
	}

	void Sprite::setColor(float r, float g, float b, float a)
	{
		Red = r;
		Green = g;
		Blue = b;
		Alpha = a;
	}

	// TRANSFORM
	const Vec2& Sprite::getPosition() const
	{
		return NewTexturePosition;
	}

	void Sprite::setPosition(const Vec2& pos)
	{
		NewTexturePosition = pos;
	}

	float Sprite::getAngle() const
	{
		return Angle;
	}

	void Sprite::setAngle(float angle)
	{
		Angle = angle;
	}

	const Vec2& Sprite::getScale() const
	{
		return Scale;
	}

	void Sprite::setScale(const Vec2& scale)
	{
		Scale = scale;
	}

	// Tamaño de un frame multiplicado por la escala
	Vec2 Sprite::getSize() const
	{
		return Vec2(getTexture()->width * Scale.x, getTexture()->height * Scale.y);
	}

	// Este valor se pasa a ltex_drawrotsized en el pintado
	// para indicar el pivote de rotación
	const Vec2& Sprite::getPivot() const
	{
		return Pivot;
	}

	void Sprite::setPivot(const Vec2& pivot)
	{
		Pivot = pivot;
	}

	int Sprite::getHframes() const
	{
		return hFrames;
	}

	int Sprite::getVframes() const
	{
		return vFrames;
	}


	// Veces por segundo que se cambia el frame de animación
	int Sprite::getFps() const
	{
		return Fps;
	}
	void Sprite::setFps(int fps)
	{
		Fps = fps;
	}

	// Frame actual de animación
	float Sprite::getCurrentFrame() const
	{
		return Frame;
	}

	void Sprite::setCurrentFrame(int frame)
	{
		Frame = frame;
	}

	void Sprite::update(float deltaTime)
	{

		Vec2 UpdatePosition = Vec2(getPosition().x + 1 * deltaTime, getPosition().y + 1 * deltaTime);
		setPosition(UpdatePosition);
		NewTexturePosition = getPosition();

		if (OldTexturePosition.x <= NewTexturePosition.x && getAngle() <= 15)
		{
			setAngle(getAngle() + 64 * deltaTime);

			if (getAngle() > 15)
			{
				setAngle(15);
			}
		}

		else if (OldTexturePosition.x >= NewTexturePosition.x && getAngle() >= -15)
		{
			setAngle(getAngle() - 64 * deltaTime);

			if (getAngle() < -15)
			{
				setAngle(-15);
			}
		}

		if (OldTexturePosition.x == NewTexturePosition.x)
		{
			setAngle(0);
		}


		OldTexturePosition = NewTexturePosition;


		// Logica para sacar la actualizacion cada x Segundos (definido en getFps())
		int numDividedForFps = 60 / getFps();
		int setUpdateFrames = 60 / numDividedForFps;

		// Nos aseguramos que siempre se reinicie la imagen despues de llegar al ultimo frame
		if (getCurrentFrame() + 1 > getHframes())
		{
			setCurrentFrame(0);
		}

		frameTime++;

		// Realizamos el update del sprite si es el momento
		if (fps / frameTime <= setUpdateFrames)
		{
			InitialFrameSize = (getCurrentFrame() / 8);
			FinalFrameSize = (getCurrentFrame() + 1) / 8;
			setCurrentFrame(getCurrentFrame() + 1);

			frameTime = 0;
		}

	}

	void Sprite::draw() const
	{
		ltex_drawrotsized(getTexture(), getPosition().x, getPosition().y, getAngle(), getPivot().x, getPivot().y, getSize().x*0.125, getSize().y, InitialFrameSize, 0, FinalFrameSize, 1);
	}


	void Sprite::setCollisionType(CollisionType type) 
	{
		TCollision = type;
	}

	Sprite::CollisionType Sprite::getCollisionType() const
	{
		return TCollision;
	}


	const Collider* Sprite::getCollider() const 
	{
		return 0;
	}

	bool Sprite::checkCollision(Sprite other)
	{
		if (getPosition().x < other.getPosition().x + other.getSize().x &&
			getPosition().x + getSize().x > other.getPosition().x &&
			getPosition().y < other.getPosition().y + other.getSize().y &&
			getPosition().y + getSize().y > other.getPosition().y)
		{
			if (collides(other)) 
			{
				
				if (getCollisionType() == COLLISION_CIRCLE) 
				{
					
					if (other.getCollisionType() == COLLISION_CIRCLE) 
					{
						CircleCollider CCollider;
						//(Ball.getPosition().x + Ball.getSize().x / 2) - (Ball.getPosition().x + Ball.getSize().x)
						float r1 = (getSize().x / 2);
						float r2 = (other.getSize().x / 2);
						Vec2 position1 = Vec2(getPosition().x + getSize().x / 2, getPosition().y + getSize().x / 2);
						Vec2 position2 = Vec2(other.getPosition().x + other.getSize().x / 2, other.getPosition().y + other.getSize().y / 2);
						if (CCollider.checkCircleCircle(position1, r1 , position2, r2))
						{
							return true;
						}
						return false;
					}
					else if (other.getCollisionType() == COLLISION_RECT)
					{
						CircleCollider CCollider;
						Vec2 position1 = Vec2(getPosition().x + getSize().x / 2, getPosition().y + getSize().x / 2);
						float r1 = (getSize().x / 2);

						Vec2 position2 = Vec2(other.getPosition().x + other.getSize().x / 2, other.getPosition().y + other.getSize().y / 2);
						Vec2 RectSize = other.getSize();

						if (CCollider.checkCircleRect(position1, r1, position2, RectSize))
						{
							return true;
						}
						return false;
					}
					else if (other.getCollisionType() == COLLISION_PIXELS)
					{
						printf("C-P Collision\n");
						return true;
					}
					return false;
				}
				else if(getCollisionType() == COLLISION_RECT)
				{
					if (other.getCollisionType() == COLLISION_CIRCLE)
					{
						CircleCollider CCollider;
						Vec2 position1 = Vec2(other.getPosition().x + other.getSize().x / 2, other.getPosition().y + other.getSize().x / 2);
						float r1 = (other.getSize().x / 2);
						Vec2 position2 = Vec2(getPosition().x + getSize().x / 2, getPosition().y + getSize().y / 2);
						Vec2 RectSize = getSize();
						if (CCollider.checkCircleRect(position1, r1, position2, RectSize))
						{
							return true;
						}
						return false;
					}
					else if (other.getCollisionType() == COLLISION_RECT)
					{
						RectCollider Collider;
						if (Collider.checkRectRect(getPosition(), getSize(), other.getPosition(), other.getSize()))
						{
							printf("R-R Collision\n");
							return true;
						}
						
						
					}
					else if (other.getCollisionType() == COLLISION_PIXELS)
					{
						RectCollider Collider;
						
						if (Collider.checkPixelsRect(other.getPosition(), other.getSize(), other.getPixels(), getPosition(), getSize()))
						{
							printf("R-P Collision\n");
							return true;
						}
					}
					return false;
					
				}
				else if (getCollisionType() == COLLISION_PIXELS)
				{
					if (other.getCollisionType() == COLLISION_CIRCLE)
					{
						printf("P-C Collision\n");
						return true;
					}
					else if (other.getCollisionType() == COLLISION_RECT)
					{
						RectCollider Collider;
						if(Collider.checkPixelsRect(getPosition(), getSize(), getPixels(), other.getPosition(), other.getSize()))
						{
							//printf("P-R Collision\n");
							return true;
						}
						
					}
					else if (other.getCollisionType() == COLLISION_PIXELS)
					{
						printf("P-P Collision\n");
						return true;
					}	
					return false;
				}
			}
			return false;
		}
		return false;
	}



	bool Sprite::collides(const Sprite& other)  const
	{
		if (getCollisionType() != Sprite::COLLISION_NONE && other.getCollisionType() != Sprite::COLLISION_NONE)
		{
			return true;
		}
		else 
		{
			return false;
		}
	}





	void Sprite::setCallback(CallbackFunc func)
	{

	}

	// Puntero genérico a datos (normalmente introducimos aquí los datos
	// del sprite que se van a utilizar en la función callback)
	void* Sprite::getUserData()
	{
		return 0;
	}

	void Sprite::setUserData(void* data)
	{

	}
