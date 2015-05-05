#include "InteractiveObjectFactory.h"
#include <math.h>
#include "InteractiveObject.h"

InteractiveObjectFactory::~InteractiveObjectFactory()
{
}

InteractiveObjectFactory::InteractiveObjectFactory()
{
}

InteractiveObjectFactory* InteractiveObjectFactory::create(int resourceIndex, bool isAnimated, bool canBeFiredAt /*= false*/, bool canHitPlayer /*= false*/)
{
	InteractiveObjectFactory* factory = new InteractiveObjectFactory();

	factory->setCanBeFiredAt(canBeFiredAt);
	factory->setCanHitPlayer(canHitPlayer);
	factory->setResource(resourceIndex);
	factory->setIsAnimated(isAnimated);

	//Default speed
	factory->setSpeed(Vec2(0, 0));

	//Default spawn interval
	factory->setSpawnFrequency(50);

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
	unsigned int randomNumber = rand() % 101;

	if (randomNumber < frequency)
	{
		InteractiveObject* newObject = InteractiveObject::create(resourceIndex, isAnimated);
		newObject->setSpeed(speed);
		newObject->setCanBeFiredAt(canBeFiredAt);
		newObject->setCanHitPlayer(canHitPlayer);

		this->objects.push_back(newObject);
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