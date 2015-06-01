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
		bullet->hit = false;

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

	Size screenSize = Director::getInstance()->getWinSize();
	Size bulletSize = this->getBoundingBox().size;
	
	if (this->getPositionX() - bulletSize.width / 2 >= screenSize.width)
		removeFromParentAndCleanup(true);
}

void Bullet::isHit()
{
	hit = true;
}
