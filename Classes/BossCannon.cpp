#include "BossCannon.h"
#include "ResourceLoader.h"
#include "GameValues.h"


BossCannon::BossCannon()
{
}


BossCannon::~BossCannon()
{
}

void BossCannon::update(float delta)
{
	framesPassed++;

	switch (currentFireState){
		case DONT_FIRE:
			break;
		case METHOD1:
			fireMethod1();
			break;
		case METHOD2:
			//fireMethod2();
			break;
		case METHOD3:
			//fireMethod3();
			break;
		default:
			break;
	}
}

BossCannon* BossCannon::create(int spriteIndex, int destroyedSpriteIndex, int cannonProjectile)
{
	BossCannon* cannon = new BossCannon();

	if (cannon->initWithFile(ResourceLoader::getImageFile(spriteIndex)))
	{
		cannon->autorelease();
		cannon->scheduleUpdate();
		cannon->HP = 100;
		cannon->destroyedSpriteIndex = destroyedSpriteIndex;
		cannon->cannonProjectile = cannonProjectile;
		cannon->destroyed = false;
		cannon->currentFireState = FireState::DONT_FIRE;
		cannon->framesPassed = 0;
		return cannon;
	}

	CC_SAFE_DELETE(cannon);
	return NULL;
}

int BossCannon::getHP()
{
	return this->HP;
}

void BossCannon::reduceHP(int amount)
{
	this->HP -= amount;
}

void BossCannon::destroyCannon()
{
	this->removeFromPhysicsWorld();
	this->initWithFile(ResourceLoader::getImageFile(destroyedSpriteIndex));
	this->destroyed = true;
}

void BossCannon::setPhysics()
{
	auto spriteBody = PhysicsBody::createBox(this->boundingBox().size, PhysicsMaterial(1.0f, 0.5f, 0.5f));
	spriteBody->setGravityEnable(false);
	spriteBody->setCollisionBitmask(BOSS_CANNON_COLLISION_BITMASK);
	spriteBody->setContactTestBitmask(true);
	spriteBody->setDynamic(false);
	this->setPhysicsBody(spriteBody);
}

bool BossCannon::isDestroyed()
{
	return this->destroyed;
}

void BossCannon::fireMethod1()
{
	Vec2 startPosition;
	startPosition.x = this->getPositionX() - this->getBoundingBox().size.width / 2;
	startPosition.y = this->getPositionY();

	if (framesPassed >= 10){
		//BossBullet* bullet = BossBullet::create();

	}
}

// void BossCannon::setFireMethod1(int numberOfBullets, int bulletInterval, int timeToTravel, Vector<Vec2> positions, int pauseTime)
// {
// 
// }
