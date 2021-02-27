#include "World.h"


World::World(float clearRed, float clearGreen, float clearBlue, const ltex_t* back0, const ltex_t* back1, const ltex_t* back2, const ltex_t* back3)
{
	fClearRed = clearRed;
	fClearGreen = clearGreen;
	fClearBlue = clearBlue;
	lBack0 = back0;
	lBack1 = back1;
	lBack2 = back2;
	lBack3 = back3;
	
}

void World::setPlayerIdleState(EIdleState _newPlayerIdleState)
{
	playerIdleState = _newPlayerIdleState;
}


const ltex_t* World::getBackground(size_t _layer) const
{
	return nullptr;
}

void World::setScrollRatio(size_t _layer, float _ratio)
{
	scrollRatio = _ratio;
}

void World::setScrollSpeed(size_t _layer, const Vec2& _speed)
{
	scrollSpeed = _speed;
}

void World::setCameraPosition(const Vec2& _pos)
{
	cameraPosition = _pos;
}

void World::addSprite(Sprite& _sprite)
{

	allGameSprites.push_back(_sprite);

}

void World::removeSprite(Sprite& _sprite)
{
	int index = 0;
	for each (Sprite actualSprite in allGameSprites)
	{	
		if (actualSprite.getTexture() == _sprite.getTexture())
		{
			allGameSprites.erase(allGameSprites.begin() + index);
			return;
		}
		index++;
	}
}

void World::update(float _deltaTime)
{
	lgfx_setorigin(getCameraPosition().x, getCameraPosition().y);

	for each(Sprite nextSprite in allGameSprites)
	{
		Vec2* updatedPosition = new Vec2(nextSprite.getPosition().x, nextSprite.getPosition().y);
		float updatedPositonX = updatedPosition->x;
		float updatedPositonY = updatedPosition->y;
		
		if(getPlayerIdleState() == EIdleState::RIGHT)
		{
			--updatedPositonX* _deltaTime * nextSprite.getScrollRatio();
			--updatedPositonY* _deltaTime * nextSprite.getScrollRatio();
			cameraPosition.x++* _deltaTime;
		} else if(getPlayerIdleState() == EIdleState::LEFT)
		{
			++updatedPositonX* _deltaTime * nextSprite.getScrollRatio();
			++updatedPositonY* _deltaTime * nextSprite.getScrollRatio();
			cameraPosition.x--* _deltaTime;
		}
		nextSprite.setPosition(*updatedPosition);
		
	}

}

void World::draw(const Vec2& _screenSize)
{
	lgfx_clearcolorbuffer(fClearRed, fClearGreen, fClearBlue);
	for each (Sprite nextSprite in allGameSprites)
	{
		if(nextSprite.getSpriteType() == ESpriteType::SINGULAR){ nextSprite.draw(1); }
		if(nextSprite.getSpriteType() == ESpriteType::HORIZONTALBACKGROUND) 
		{
			int numOfImages = _screenSize.x / nextSprite.getSize().x;
			numOfImages++;
			lgfx_setblend(BLEND_ALPHA);
			ltex_drawrotsized(nextSprite.getTexture(),
				nextSprite.getPosition().x, nextSprite.getPosition().y,
				nextSprite.getAngle(),
				nextSprite.getPivot().x, nextSprite.getPivot().y,
				nextSprite.getSize().x * numOfImages, nextSprite.getSize().y * numOfImages,
				0, 0,
				numOfImages, numOfImages);
		}
		if(nextSprite.getSpriteType() == ESpriteType::FULLBACKGROUND)
		{
			int numOfImages = _screenSize.x / nextSprite.getSize().x;
			numOfImages++;
			lgfx_setblend(BLEND_ALPHA);
			ltex_drawrotsized(nextSprite.getTexture(),
				nextSprite.getPosition().x, nextSprite.getPosition().y,
				nextSprite.getAngle(),
				nextSprite.getPivot().x, nextSprite.getPivot().y,
				nextSprite.getSize().x * numOfImages, nextSprite.getSize().y * numOfImages,
				0, 0,
				numOfImages, numOfImages);
		}
	}
}

