#pragma once

#include <vector>
#include "Vec2.h"
#include "Sprite.h"

class World 
{
private:

	float fClearRed, fClearGreen, fClearBlue;
	const ltex_t* lBack0;
	const ltex_t* lBack1;
	const ltex_t* lBack2;
	const ltex_t* lBack3;
	std::vector<Sprite> allGameSprites;

	Vec2 scrollSpeed;
	float scrollRatio;
	Vec2 cameraPosition;
	EIdleState playerIdleState = EIdleState::IDLE;

public:

	World(float clearRed = 0.15f, float clearGreen = 0.15f, float clearBlue = 0.15f,
		const ltex_t* back0 = nullptr, const ltex_t* back1 = nullptr, const ltex_t* back2 = nullptr, const ltex_t* back3 = nullptr);

	EIdleState getPlayerIdleState() { return playerIdleState; }
	void setPlayerIdleState(EIdleState _newPlayerIdleState);

	float getClearRed() const { return fClearRed; }
	float getClearGreen() const { return fClearGreen; }
	float getClearBlue() const { return fClearBlue; }

	const ltex_t* getBackground(size_t layer) const;

	float getScrollRatio(size_t layer) const { return scrollRatio; }
	void setScrollRatio(size_t layer, float ratio);

	const Vec2& getScrollSpeed(size_t layer) const { return scrollSpeed; }
	void setScrollSpeed(size_t layer, const Vec2& speed);

	const Vec2& getCameraPosition() const { return cameraPosition; }
	void setCameraPosition(const Vec2& pos);

	void addSprite(Sprite& sprite);
	void removeSprite(Sprite& sprite);

	void update(float deltaTime);
	void draw(const Vec2& screenSize);
};