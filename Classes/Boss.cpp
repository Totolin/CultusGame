#include "Boss.h"
#include "ResourceLoader.h"
#include "GameValues.h"
#include "BossCannon.h"


Boss::Boss()
{
}


Boss::~Boss()
{
}

void Boss::update(float delta)
{
	for (int i = 0; i < cannons[cannonsArrayStateIndex].size(); i++)
	{
		if (cannons[cannonsArrayStateIndex].at(i)->getHP() <= 0 && !cannons[cannonsArrayStateIndex].at(i)->isDestroyed())
		{
			cannons[cannonsArrayStateIndex].at(i)->destroyCannon();
			numberOfDestroyedCannons++;
		}
	}

	switch (this->currentState)
	{
		case State::AWAITING:
			break;
		case State::MOVE_IN:
			moveX(-3);
			if (this->positionToMove.x >= this->getPosition().x) {nextState();}
			break;
		case State::GO_TO_MODE_1:
			changeCannons();
			nextState();
			break;
		case State::FIRST_MODE:
			if(checkCannonsStatus()) { 
				nextState();
			}
			break;
		case State::GO_TO_MODE_2:
			cannonsArrayStateIndex++;
			changeCannons();
			nextState();
		case State::SECOND_MODE:
 			if (checkCannonsStatus()) {
				nextState();
			}
			break;
		case State::GO_TO_MODE_3:
			cannonsArrayStateIndex++;
			setPhysics();
		default:
			break;
	}
}

Boss* Boss::create(int spriteIndex)
{
	Boss* boss = new Boss();

	if (boss->initWithFile(ResourceLoader::getImageFile(spriteIndex)))
	{
		boss->autorelease();
		boss->scheduleUpdate();
		boss->setScale(1.7);

		Size boundingBox = boss->getBoundingBox().size;
		int positionX = Director::getInstance()->getWinSize().width + boundingBox.width / 2;
		int positionY = boundingBox.height / 2 + 100;
		boss->cannonsArrayStateIndex = 0;
		boss->setPosition(Vec2(positionX, positionY));
		boss->setState(State::AWAITING);
		return boss;
	}

	CC_SAFE_DELETE(boss);
	return NULL;
}

void Boss::moveIn(Vec2 position)
{
	this->positionToMove = position;
	this->nextState();
}

void Boss::setPhysics()
{
	auto spriteBody = PhysicsBody::createBox(this->boundingBox().size, PhysicsMaterial(1.0f, 0.5f, 0.5f));
	spriteBody->setGravityEnable(false);
	spriteBody->setCollisionBitmask(BOSS_COLLISION_BITMASK);
	spriteBody->setContactTestBitmask(true);
	this->setPhysicsBody(spriteBody);
}
 
void Boss::updatePlayerPosition(Vec2 playerPosition)
{
	if (currentState >= 7) { return; }

	for (int i = 0; i < cannons[cannonsArrayStateIndex].size(); i++)
	{
		cannons[cannonsArrayStateIndex].at(i)->updatePlayerPosition(playerPosition);
	}
}

void Boss::nextState()
{
	currentState++;
}

// Move a player on the X axis by a set number of pixels
// @param pixelsToMove - Number of pixels to move
// @return - Bool which states if the key is pressed or not
void Boss::moveX(int pixelsToMove)
{
	Vec2 loc = this->getPosition();
	loc.x += pixelsToMove;
	this->setPosition(loc); 
}

// Move a player on the Y axis by a set number of pixels
// @param pixelsToMove - Number of pixels to move
void Boss::moveY(int pixelsToMove)
{
	Vec2 loc = this->getPosition();
	loc.y += pixelsToMove;
	this->setPosition(loc);
}

void Boss::setState(State state)
{
	this->currentState = state;
}

void Boss::addCannon(int stateOfParent, BossCannon* cannon)
{
	cannons[stateOfParent - 1].pushBack(cannon);
	this->addChild(cannon);
}

void Boss::changeCannons()
{
	numberOfDestroyedCannons = 0;
	for (int i = 0; i < cannons[cannonsArrayStateIndex].size(); i++)
	{
		cannons[cannonsArrayStateIndex].at(i)->setPhysics();
		cannons[cannonsArrayStateIndex].at(i)->nextState();
	}
}

bool Boss::checkCannonsStatus()
{
	if (numberOfDestroyedCannons == cannons[cannonsArrayStateIndex].size())
	{
		return true;
	}

	return false;
}
