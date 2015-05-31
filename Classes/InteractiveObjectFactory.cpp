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
	factory->scheduleUpdate();

	//Default speed
	factory->setSpeed(Vec2(-10, 0));

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
		this->objects.push_back(newObject);
	}
}

void InteractiveObjectFactory::update(float delta)
{
	if (objects.size() > 0)
	{
		Size objectSize = objects.at(0)->getBoundingBox().size;
		Vec2 position = objects.at(0)->getPosition();

		if (position.x + (objectSize.width / 2) <=0 || position.y < 0)
		{
			objects.at(0)->getParent()->removeChild(objects.at(0));
			objects.erase(objects.begin());

			if (position.y < 0) {
				CCLOG("Object fell down");
			}
			else
			{
				CCLOG("Object exit screen (Left Side)");
			}
		}
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