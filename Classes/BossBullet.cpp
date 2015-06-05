#include "ResourceLoader.h"
#include "GameValues.h"
#include "BossBullet.h"

BossBullet* BossBullet::create(int bulletFileIndex)
{
	BossBullet* bullet = new BossBullet();

	if (bullet->initWithFile(ResourceLoader::getImageFile(bulletFileIndex)))
	{
		bullet->autorelease();
		bullet->scheduleUpdate();
		bullet->hit = false;
		bullet->explodeOnGround = false;
		auto spriteBody = PhysicsBody::createCircle(bullet->boundingBox().size.width/2, PhysicsMaterial(1.0f, 0.5f, 0.5f));
		spriteBody->setGravityEnable(false);
		spriteBody->setCollisionBitmask(BOSSBULLET_COLLISION_BITMASK);
		spriteBody->setContactTestBitmask(true);
		bullet->setPhysicsBody(spriteBody);

		return bullet;
	}

	CC_SAFE_DELETE(bullet);
	return NULL;
}



void BossBullet::update(float delta)
{
	Size screenSize = Director::getInstance()->getWinSize();
	Size bulletSize = this->getBoundingBox().size;

	// Delete bullet if out of the screen
	if (this->getPositionX() + bulletSize.width / 2 <= 0)
		removeFromParentAndCleanup(true);
	else if (this->getPositionY() - bulletSize.height / 2 >= screenSize.height)
		removeFromParentAndCleanup(true);
	else if (this->getPositionY() + bulletSize.height / 2 <= 0)
		removeFromParentAndCleanup(true);
}

void BossBullet::isHit()
{
	hit = true;
}

void BossBullet::setExplodeOnGround(bool b)
{
	explodeOnGround = b;
}

bool BossBullet::getExplodeOnGround()
{
	return explodeOnGround;
}