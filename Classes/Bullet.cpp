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
		bullet->setScale(Director::getInstance()->getWinSize().width * 0.8 / 800);
		bullet->hit = false;
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



void Bullet::update(float delta)
{
	// Move the bullet
	//this->getPhysicsBody()->setVelocity(Vect(300, 0));
	this->setPositionX(this->getPositionX() + 30);

	Size screenSize = Director::getInstance()->getWinSize();
	Size bulletSize = this->getBoundingBox().size;
	
	// Delete bullet if out of the screen
	if (this->getPositionX() - bulletSize.width / 2 >= screenSize.width)
		removeFromParentAndCleanup(true);
}

void Bullet::isHit()
{
	hit = true;
}
