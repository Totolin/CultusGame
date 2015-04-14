#include "ParallaxSprite.h"

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

void ParallaxSprite::setVelocityFactor(Vec2& velocity)
{
	this->velocity = velocity;
}

Vec2& ParallaxSprite::getVelocityFactor()
{
	return velocity;
}