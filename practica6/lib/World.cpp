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

float World::getClearRed() const
{
	return fClearRed;
}

float World::getClearGreen() const
{
	return fClearGreen;
}

float World::getClearBlue() const
{
	return fClearBlue;
}

const ltex_t* World::getBackground(size_t _layer) const
{
	return nullptr;
}

float World::getScrollRatio(size_t _layer) const
{
	return 0.0f;
}

void World::setScrollRatio(size_t _layer, float _ratio)
{
	scrollRatio = _ratio;
}

const Vec2& World::getScrollSpeed(size_t _layer) const
{
	return Vec2(0, 0);
}

void World::setScrollSpeed(size_t _layer, const Vec2& _speed)
{
	scrollSpeed = _speed;
}

const Vec2& World::getCameraPosition() const
{
	return Vec2(0, 0);
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

}

void World::draw(const Vec2& _screenSize)
{
	lgfx_clearcolorbuffer(fClearRed, fClearGreen, fClearBlue);
	for each (Sprite nextSprite in allGameSprites)
	{
		nextSprite.draw(1);
	}

	lgfx_setorigin(getCameraPosition().x, getCameraPosition().y);
}
