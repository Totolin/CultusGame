#include "Bullet.h"
#include "ResourceLoader.h"
#include "GameValues.h"

Bullet* Bullet::create(int bulletFileIndex)
{
	Bullet* bullet = new Bullet();

	if (bullet->initWithFile(ResourceLoader::getBulletFile(bulletFileIndex)))
	{
		bullet->autorelease();
		bullet->scheduleUpdate();
		auto spriteBody = PhysicsBody::createBox(bullet->boundingBox().size, PhysicsMaterial(1.0f, 0.5f, 0.5f));
		spriteBody->setGravityEnable(false);
		spriteBody->setCollisionBitmask(BULLET_COLLISION_BITMASK);
		spriteBody->setContactTestBitmask(true);
		bullet->setPhysicsBody(spriteBody);

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