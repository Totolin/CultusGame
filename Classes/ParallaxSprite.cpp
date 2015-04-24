#include "ParallaxSprite.h"

// Creates an instance of ParallaxSprite class
// A ParallaxBackground contains multiple ParallaxSprites, which
// have their own background images and move individually with different
// speeds (velocities).
// @param imgName - Path to the background image
ParallaxSprite* ParallaxSprite::create(string imgName)
{
	ParallaxSprite* pSprite = new ParallaxSprite();

	if (pSprite->initWithFile(imgName))
	{
		pSprite->autorelease();
		return pSprite;
	}

	CC_SAFE_DELETE(pSprite);
	return NULL;
}

// Sets the speed (velocity) for moving the ParallaxSprite
void ParallaxSprite::setVelocityFactor(Vec2& velocity)
{
	this->velocity = velocity;
}

// Gets the speed(velocity) of the ParallaxSprite
// @return Vec2& - Velocity of the Sprite
Vec2& ParallaxSprite::getVelocityFactor()
{
	return velocity;
}