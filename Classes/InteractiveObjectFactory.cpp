#include "InteractiveObjectFactory.h"
#include "GameValues.h"
#include "InteractiveObject.h"

InteractiveObjectFactory::~InteractiveObjectFactory()
{
}

InteractiveObjectFactory::InteractiveObjectFactory()
{
}

void InteractiveObjectFactory::setGravityAffected(bool gravityAffected)
{
	this->gravityAffected = gravityAffected;
}

InteractiveObjectFactory* InteractiveObjectFactory::create(int resourceIndex, float scaleFactor, bool isAnimated, int maskValue, bool canBeFiredAt /*= false*/, bool canHitPlayer /*= false*/, bool gravityAffected)
{
	InteractiveObjectFactory* factory = new InteractiveObjectFactory();
	factory->maskValue = maskValue;
	factory->scaleFactor = scaleFactor;
	factory->setCanBeFiredAt(canBeFiredAt);
	factory->setCanHitPlayer(canHitPlayer);
	factory->setResource(resourceIndex);
	factory->setIsAnimated(isAnimated);
	factory->setGravityAffected(gravityAffected);
	factory->framePassed = 15;
	//Default speed
	factory->setSpeed(Vec2(-9, 0));

	//Default spawn interval
	factory->setSpawnFrequency(20);

	//Default position interval
	factory->setPositionInterval(Vec2(0, 0));
	
	return factory;
}

void InteractiveObjectFactory::setSpeed(Vec2 speed)
{
	this->speed = speed;
}

void InteractiveObjectFactory::setSpawnFrequency(int frequency)
{
	this->frequency = frequency;
}

void InteractiveObjectFactory::setPositionInterval(Vec2 interval)
{
	this->spawnInterval = interval;
}

void InteractiveObjectFactory::createObject()
{
	if (framePassed > 0)
	{
		framePassed--;
		return;
	}

	unsigned int randomNumber = RandomHelper::random_int<int>(1, 500);

	if (randomNumber < frequency)
	{
		// Get random spawn position
		unsigned int randomYpos = RandomHelper::random_int<int>(spawnInterval.x,spawnInterval.y);

		// Create object
		InteractiveObject* newObject = InteractiveObject::create(resourceIndex,maskValue, isAnimated);

		// Set members
		newObject->setSpeed(speed);
		newObject->setCanBeFiredAt(canBeFiredAt);
		newObject->setCanHitPlayer(canHitPlayer);
		newObject->setPosition(Director::getInstance()->getWinSize().width + (newObject->boundingBox().size.width) / 2 + 20, randomYpos);
		newObject->setGravityAffected(gravityAffected);
		newObject->setScale(scaleFactor);
		framePassed = 15;
			
		Director::getInstance()->getRunningScene()->getChildByTag(LAYER_TAG)->addChild(newObject);
	}
}


void InteractiveObjectFactory::setIsAnimated(bool isAnimated)
{
	this->isAnimated = isAnimated;
}

void InteractiveObjectFactory::setCanBeFiredAt(bool canBeFiredAt)
{
	this->canBeFiredAt = canBeFiredAt;
}

void InteractiveObjectFactory::setCanHitPlayer(bool canHitPlayer)
{
	this->canHitPlayer = canHitPlayer;
}

void InteractiveObjectFactory::setResource(int resource)
{
	this->resourceIndex = resource;
}

void InteractiveObjectFactory::setParent(GameLayer* parent)
{
	this->parent = parent;
}