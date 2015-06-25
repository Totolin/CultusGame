#include "InteractiveObject.h"
#include "ResourceLoader.h"
#include "GameValues.h"

InteractiveObject::InteractiveObject()
{
}

InteractiveObject::~InteractiveObject()
{
}

InteractiveObject* InteractiveObject::create(int resourceIndex, int maskValue, bool isAnimated)
{
	// Create an instance of Player
	InteractiveObject* objectSprite = new InteractiveObject();

	// Get resource loader instance
	ResourceLoader resLoader = ResourceLoader::getInstance();

	objectSprite->hasBeenHit = false;

	if (isAnimated)
	{
		// Get running animation
		Vector<SpriteFrame*> runningAnimation = resLoader.getAnimation(resourceIndex);

		if (objectSprite->initWithSpriteFrame(runningAnimation.at(0)))
		{
			auto animation = Animation::createWithSpriteFrames(runningAnimation);

			// Set delay between frames
			animation->setDelayPerUnit(OBJECT_SPRITE_DELAY_ANIMATION);

			//Create running action
			auto runningAction = RepeatForever::create(Animate::create(animation));

			// Run animation forever
			objectSprite->runAction(runningAction);

			// Set properties
			objectSprite->autorelease();
			objectSprite->setScale(Director::getInstance()->getWinSize().width * 2 / 800);
			objectSprite->scheduleUpdate();

			if (objectSprite->getCanBeFireAt() || objectSprite->getCanHitPlayer())
			{
				auto spriteBody = PhysicsBody::createBox(objectSprite->boundingBox().size, PhysicsMaterial(1.0f, 0.5f, 0.5f));
				spriteBody->setGravityEnable(objectSprite->isGravityAffected());
				spriteBody->setCollisionBitmask(maskValue);
				spriteBody->setContactTestBitmask(true);
				spriteBody->setMass(1);
				objectSprite->setPhysicsBody(spriteBody);
				
			}

			// Return
			return objectSprite;
		}
	}
	else
	{
		if (objectSprite->initWithFile(ResourceLoader::getImageFile(resourceIndex)))
		{
			objectSprite->autorelease();
			objectSprite->scheduleUpdate();
			objectSprite->setScale(Director::getInstance()->getWinSize().width *0.5 / 800);

			if (objectSprite->getCanBeFireAt() || objectSprite->getCanHitPlayer())
			{
				auto spriteBody = PhysicsBody::createBox(objectSprite->boundingBox().size, PhysicsMaterial(1.0f, 0.5f, 0.5f));
				bool affected = objectSprite->isGravityAffected();
				spriteBody->setGravityEnable(objectSprite->isGravityAffected());
				spriteBody->setCollisionBitmask(maskValue);
				spriteBody->setMass(1);
				spriteBody->setContactTestBitmask(true);
				objectSprite->setPhysicsBody(spriteBody);
			}

			return objectSprite;
		}
	}

	CC_SAFE_DELETE(objectSprite);
	return NULL;
}

void InteractiveObject::setSpeed(Vec2 speed)
{
	this->speed = speed;
}

void InteractiveObject::setCanBeFiredAt(bool canBeFiredAt)
{
	this->canBeFiredAt = canBeFiredAt;
}

void InteractiveObject::setCanHitPlayer(bool canHitPlayer)
{
	this->canHitPlayer = canHitPlayer;
}

bool InteractiveObject::getCanBeFireAt()
{
	return canBeFiredAt;
}

bool InteractiveObject::getCanHitPlayer()
{
	return canHitPlayer;
}

void InteractiveObject::setGravityAffected(bool gravityAffected)
{
	this->getPhysicsBody()->setGravityEnable(gravityAffected);
	this->gravityAffected = gravityAffected;
}

bool InteractiveObject::isGravityAffected()
{
	return gravityAffected;
}

Vec2 InteractiveObject::getSpeed()
{
	return speed;
}

void InteractiveObject::update(float delta)
{
	Size screenSize = Director::getInstance()->getWinSize();
	Size objectSize = this->getBoundingBox().size;

	if (getPositionX() + (objectSize.width / 2) <= 0 || getPositionY() < 0){
		removeFromParentAndCleanup(true);
		return;
	}


	if (hasBeenHit) return;
	//TODO: Replace vec2 with int, put in Values if necessary
	Vec2 loc = this->getPosition();
	loc.x += this->speed.x;
	this->setPosition(loc);

}

void InteractiveObject::isHit()
{
	this->hasBeenHit = true;
	this->getPhysicsBody()->setGravityEnable(false);
	this->getPhysicsBody()->applyImpulse(Vect(1000, 1000));
	this->getPhysicsBody()->applyForce(Vect(1000, 1000));
	this->getPhysicsBody()->setAngularVelocity(10);
}
