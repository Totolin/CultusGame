#include "InteractiveObjectFactory.h"
#include <math.h>
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

InteractiveObjectFactory* InteractiveObjectFactory::create(int resourceIndex, bool isAnimated, int maskValue, bool canBeFiredAt /*= false*/, bool canHitPlayer /*= false*/, bool gravityAffected)
{
	InteractiveObjectFactory* factory = new InteractiveObjectFactory();
	factory->maskValue = maskValue;
	factory->setCanBeFiredAt(canBeFiredAt);
	factory->setCanHitPlayer(canHitPlayer);
	factory->setResource(resourceIndex);
	factory->setIsAnimated(isAnimated);
	factory->setGravityAffected(gravityAffected);

	//Default speed
	factory->setSpeed(Vec2(-9, 0));

	//Default spawn interval
	factory->setSpawnFrequency(5);

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
	unsigned int randomNumber = rand() % 501;

	if (randomNumber < frequency)
	{
		// Get random spawn position
		unsigned int randomYpos = rand() % (int)((spawnInterval.y - spawnInterval.x) + spawnInterval.x);

		// Create object
		InteractiveObject* newObject = InteractiveObject::create(resourceIndex,maskValue, isAnimated);

		// Set members
		newObject->setSpeed(speed);
		newObject->setCanBeFiredAt(canBeFiredAt);
		newObject->setCanHitPlayer(canHitPlayer);
		newObject->setPosition(Director::getInstance()->getWinSize().width + (newObject->boundingBox().size.width) / 2 + 20, randomYpos);
		newObject->setGravityAffected(gravityAffected);

		Director::getInstance()->getRunningScene()->addChild(newObject);
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

void InteractiveObjectFactory::setParent(GameLevel* parent)
{
	this->parent = parent;
}