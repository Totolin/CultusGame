#include "BossCannon.h"
#include "ResourceLoader.h"
#include "GameValues.h"
#include "BossBullet.h"


BossCannon::BossCannon()
{
}


BossCannon::~BossCannon()
{
}

void BossCannon::update(float delta)
{
	// Not firing or dead
	if (currentFireState != FIRE) { return; }
	
	framesPassed++;

	// Needs to fire
	fire();

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
		cannon->playerPosition = Vec2(0, 0);
		cannon->numberOfBullets = 0;
		cannon->pauseTime = 0;
		cannon->currentFireState = FireState::DONT_FIRE;
		cannon->framesPassed = 0;
		cannon->numberOfFiredBullets = 0;
		cannon->cooldown = 0;
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
	this->currentFireState = FireState::DESTROYED;
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
	return currentFireState == FireState::DESTROYED;
}

void BossCannon::fire()
{
	if (cooldown > 0){
		cooldown--;
		framesPassed--;
		return;
	}

	if (fireMethod == 1){
		if (numberOfFiredBullets == numberOfBullets && cooldown == 0)
		{
			cooldown = pauseTime;
			numberOfFiredBullets = 0;
		}

		if (framesPassed == 10){
			// Reset counter 
			framesPassed = 0;

			// Create bullet
			BossBullet* bullet = BossBullet::create(cannonProjectile);

			// Calculate where to fire it
			Vec2 startPosition = this->getParent()->convertToWorldSpace(this->getPosition());
			startPosition.x -= this->getBoundingBox().size.width / 2;
			startPosition.x -= bullet->getBoundingBox().size.width / 2;

			float dx = playerPosition.x - startPosition.x;
			float dy = playerPosition.y - startPosition.y;
			float dlt = sqrt(dx*dx + dy*dy);

			Vec2 velocity(dx / dlt * 300, dy / dlt * 300);
			bullet->setPosition(startPosition);
			bullet->getPhysicsBody()->setVelocity(velocity);
			// Add to scene
			Director::getInstance()->getRunningScene()->getChildByTag(LAYER_TAG)->addChild(bullet);

			numberOfFiredBullets++;
		}
	}
	else if (fireMethod == 2)
	{
		if (numberOfFiredBullets == numberOfBullets && cooldown == 0)
		{
			cooldown = pauseTime;
			numberOfFiredBullets = 0;
		}

		if (framesPassed == 50){
			// Reset frames counter
			framesPassed = 0;

			// Set bullet to shoot at ground level
			this->playerPosition.y = PLAYER_GROUND;

			// Create bullet
			BossBullet* bullet = BossBullet::create(cannonProjectile);
			// Calculate where to fire it
			Vec2 startPosition = this->getParent()->convertToWorldSpace(this->getPosition());
			startPosition.x -= this->getBoundingBox().size.width / 2;
			startPosition.x -= bullet->getBoundingBox().size.width / 2;
			bullet->setPosition(startPosition);
			bullet->setExplodeOnGround(true);

			JumpTo* jump = JumpTo::create(1, playerPosition, 300, 1);
			MoveTo* move = MoveTo::create(0.3f, Vec2(playerPosition.x, playerPosition.y - 200));
			Sequence* sequence = Sequence::create(jump, move, nullptr);

			bullet->runAction(sequence);
			
			Director::getInstance()->getRunningScene()->getChildByTag(LAYER_TAG)->addChild(bullet);


			numberOfFiredBullets++;
		}
	}
}

void BossCannon::updatePlayerPosition(Vec2 position)
{
	//CCLOG((to_string(this->getPositionX()) + " " + to_string(this->getPositionY())).c_str());	
	this->playerPosition = position;
}

void BossCannon::setFireMethod(int fireMethod,int numberOfBullets, int pauseTime)
{
	this->numberOfBullets = numberOfBullets;
	this->pauseTime = pauseTime;
	this->fireMethod = fireMethod;
}

void BossCannon::nextState()
{
	this->currentFireState++;
}
