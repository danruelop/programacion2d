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

const ltex_t* World::getBackground(size_t layer) const
{
	return nullptr;
}

float World::getScrollRatio(size_t layer) const
{
	return 0.0f;
}

void World::setScrollRatio(size_t layer, float ratio)
{
	scrollRatio = ratio;
}

const Vec2& World::getScrollSpeed(size_t layer) const
{
	return Vec2(0, 0);
}

void World::setScrollSpeed(size_t layer, const Vec2& speed)
{
	scrollSpeed = speed;
}

const Vec2& World::getCameraPosition() const
{
	return Vec2(0, 0);
}

void World::setCameraPosition(const Vec2& pos)
{
	cameraPosition = pos;
}

void World::addSprite(Sprite& sprite)
{

	allGameSprites.push_back(sprite);

}

void World::removeSprite(Sprite& sprite)
{

	allGameSprites.erase(std::remove(allGameSprites.begin(), allGameSprites.end(), sprite), allGameSprites.end());

}

void World::update(float deltaTime)
{

}

void World::draw(const Vec2& screenSize)
{
	lgfx_clearcolorbuffer(fClearRed, fClearGreen, fClearBlue);
	for each (Sprite nextSprite in allGameSprites)
	{
		nextSprite.draw();
	}

	lgfx_setorigin(getCameraPosition().x, getCameraPosition().y);
}
