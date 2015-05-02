#include "Bullet.h"
#include "ResourceLoader.h"

Bullet* Bullet::create(int bulletFileIndex)
{
	Bullet* bullet = new Bullet();

	if (bullet->initWithFile(ResourceLoader::getBulletFile(bulletFileIndex)))
	{
		bullet->autorelease();
		bullet->scheduleUpdate();

		return bullet;
	}

	CC_SAFE_DELETE(bullet);
	return NULL;
}

void Bullet::moveX(int pixelsToMove)
{
	Vec2 loc = this->getPosition();
	loc.x += pixelsToMove;
	this->setPosition(loc);
}

void Bullet::update(float delta)
{
	this->moveX(20);

	// 	float screenWidth = Director::getInstance()->getWinSize().width;
	// 	float bulletWidth = this->getBoundingBox().size.width;
	//
	// 	if (this->getPositionX() - bulletWidth / 2 >= screenWidth)
	// 		release();
}