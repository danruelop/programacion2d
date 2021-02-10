#pragma once
#include "Sprite.h"


// frames en horizontal de la imagen y frames en vertical
	Sprite::Sprite(const ltex_t* _tex, int _hFrames, int _vFrames) 
	{
		tex = _tex;
		hFrames = _hFrames;
		vFrames = _vFrames;
	}

	const ltex_t* Sprite::getTexture() const
	{
		return tex;
	}

	void Sprite::setTexture(const ltex_t* _tex, int _hFrames, int _vFrames)
	{
		Sprite* newTexture = new Sprite(_tex, _hFrames, _vFrames);
	}

	lblend_t Sprite::getBlend() const 
	{
		return blendMode;
	}

	void Sprite::setBlend(lblend_t _mode) 
	{
		blendMode = _mode;
		lgfx_setblend(blendMode);
	}


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

	void Sprite::setColor(float _r, float _g, float _b, float _a)
	{
		Red = _r;
		Green = _g;
		Blue = _b;
		Alpha = _a;
	}

	const Vec2& Sprite::getPosition() const
	{
		return newPosition;
	}

	void Sprite::setPosition(const Vec2& _pos)
	{
		newPosition = _pos;
	}

	float Sprite::getAngle() const
	{
		return Angle;
	}

	void Sprite::setAngle(float _angle)
	{
		Angle = _angle;
	}

	const Vec2& Sprite::getScale() const
	{
		return Scale;
	}

	void Sprite::setScale(const Vec2& _scale)
	{
		Scale = _scale;
	}


	Vec2 Sprite::getSize() const
	{
		return Vec2(getTexture()->width * Scale.getPosX(), getTexture()->height * Scale.getPosY());
	}

	const Vec2& Sprite::getPivot() const
	{
		return Pivot;
	}

	void Sprite::setPivot(const Vec2& _pivot)
	{
		Pivot = _pivot;
	}

	int Sprite::getHFrames() const
	{
		return hFrames;
	}

	int Sprite::getVFrames() const
	{
		return vFrames;
	}

	// frecuencia de refresco para cambiar de frame
	int Sprite::getFps() const
	{
		return Fps;
	}
	void Sprite::setFps(int _fps)
	{
		Fps = _fps;
	}

	// frame actual que se ejecuta en la animación
	float Sprite::getCurrentFrame() const
	{
		return Frame;
	}

	void Sprite::setCurrentFrame(int _frame)
	{
		Frame = _frame;
	}

	void Sprite::update(float _deltaTime)
	{
		Vec2 UpdatePosition = Vec2(getPosition().getPosX() + 1 * _deltaTime, getPosition().getPosY() + 1 * _deltaTime);
		setPosition(UpdatePosition);
		newPosition = getPosition();

		if (oldPosition.getPosX() <= newPosition.getPosX() && getAngle() <= 15)
		{
			setAngle(getAngle() + 64 * _deltaTime);

			if (getAngle() > 15)
			{
				setAngle(15);
			}
		}

		else if (oldPosition.getPosX() >= newPosition.getPosX() && getAngle() >= -15)
		{
			setAngle(getAngle() - 64 * _deltaTime);

			if (getAngle() < -15) 
			{
				setAngle(-15);
			}
		}

		if (oldPosition.getPosX() == newPosition.getPosX())
		{
			setAngle(0);
		}
		

		oldPosition = newPosition;
	

		// cogemos los frames actualizados

		int updateFrames = getFps();

		if (getCurrentFrame() + 1 > getHFrames())
		{
			setCurrentFrame(0);
		}

		frameTime++;

		// Realizamos el update del sprite si es el momento
		if (fps / frameTime <= updateFrames)
		{
			iFrameSize = (getCurrentFrame() / 8);
			fFrameSize = (getCurrentFrame() + 1) / 8;
			setCurrentFrame(getCurrentFrame() + 1);
			
			frameTime = 0;
		}
	}

	void Sprite::draw() const
	{
		ltex_drawrotsized(getTexture(),
			getPosition().getPosX(), getPosition().getPosY(),
			getAngle(), getPivot().getPosX(), getPivot().getPosY(),
			getSize().getPosX() * 0.125, getSize().getPosY(),
			iFrameSize, 0, fFrameSize, 1);
	}



