#include "InteractiveObject.h"
#include "ResourceLoader.h"
#include "GameValues.h"

InteractiveObject::InteractiveObject()
{
}

InteractiveObject::~InteractiveObject()
{
}

InteractiveObject* InteractiveObject::create(int resourceIndex, bool isAnimated)
{
	// Create an instance of Player
	InteractiveObject* objectSprite = new InteractiveObject();

	// Get resource loader instance
	ResourceLoader resLoader = ResourceLoader::getInstance();

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
			objectSprite->setScale(2);
			objectSprite->scheduleUpdate();

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

void InteractiveObject::update(float delta)
{
	//TODO: Replace vec2 with int, put in Values if necessary
	Vec2 loc = this->getPosition();
	loc.x += this->speed.x;
	this->setPosition(loc);
}