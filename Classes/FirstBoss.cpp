#include "FirstBoss.h"
#include "ResourceLoader.h"
#include "GameValues.h"
#include "BossCannon.h"


FirstBoss::FirstBoss()
{
}


FirstBoss::~FirstBoss()
{
}

void FirstBoss::update(float delta)
{
	if (cannon1->getHP() <= 0)
	{
		cannon1->destroyCannon();
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
			cannon1->setPhysics();
			cannon1->nextState();
			nextState();
			break;
		case State::FIRST_MODE:
			if(cannon1->isDestroyed()) { 
				nextState();
			}
			break;
		case State::GO_TO_MODE_2:
			setPhysics();
		default:
			break;
	}
}

FirstBoss* FirstBoss::create(int spriteIndex)
{
	FirstBoss* boss = new FirstBoss();

	if (boss->initWithFile(ResourceLoader::getImageFile(spriteIndex)))
	{
		boss->autorelease();
		boss->scheduleUpdate();
		boss->setScale(1.7);

		Size boundingBox = boss->getBoundingBox().size;
		int positionX = Director::getInstance()->getWinSize().width + boundingBox.width / 2;
		int positionY = boundingBox.height / 2 + 100;

		boss->setPosition(Vec2(positionX, positionY));
		boss->setState(State::AWAITING);
		return boss;
	}

	CC_SAFE_DELETE(boss);
	return NULL;
}



void FirstBoss::moveIn(Vec2 position)
{
	this->positionToMove = position;
	this->nextState();
}

void FirstBoss::setPhysics()
{
	auto spriteBody = PhysicsBody::createBox(this->boundingBox().size, PhysicsMaterial(1.0f, 0.5f, 0.5f));
	spriteBody->setGravityEnable(false);
	spriteBody->setCollisionBitmask(BOSS_COLLISION_BITMASK);
	spriteBody->setContactTestBitmask(true);
	this->setPhysicsBody(spriteBody);
}

void FirstBoss::addCannon_1(int cannonIndexAlive, int cannonIndexDestroyed, int cannonProjectile)
{
	BossCannon* cannon = BossCannon::create(cannonIndexAlive, cannonIndexDestroyed, cannonProjectile);
	cannon->setPosition(Vec2(70, 100));
	this->addChild(cannon);
	cannon1 = cannon;
}
 
void FirstBoss::updatePlayerPosition(Vec2 playerPosition)
{
	this->cannon1->updatePlayerPosition(playerPosition);
}
