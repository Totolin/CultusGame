#include "GameLevel.h"
#include "UIBar.h"
#include "BossCannon.h"

GameLevel::GameLevel()
{
}

GameLevel::~GameLevel()
{
}

void GameLevel::setBoss(Boss* levelBoss)
{
	this->levelBoss = levelBoss;
	this->addChild(levelBoss);
}

void GameLevel::setBackground(ParallaxBackground* levelBackground)
{
	this->levelBackground = levelBackground;
	this->addChild(levelBackground);
}

void GameLevel::setPlayer(Player* mainCharacter)
{
	this->mainCharacter = mainCharacter;
	this->addChild(mainCharacter);
}

void GameLevel::setDistanceToBoss(long long distance)
{
	this->distance = distance;
}

void GameLevel::setAudioEngine(CocosDenshion::SimpleAudioEngine* audioEngine)
{
	this->audioEngine = audioEngine;
}

void GameLevel::setMusic(string backgroundMusic)
{
	this->backgroundMusic = backgroundMusic;
}

void GameLevel::addObjectFactory(InteractiveObjectFactory* objectFactory)
{
	this->objectFactories.push_back(objectFactory);
}

GameLevel* GameLevel::create()
{
	GameLevel* gameLevel = GameLevel::createWithPhysics();
	gameLevel->getPhysicsWorld()->setGravity(Vect(0.0f, -700.0f));
	gameLevel->getPhysicsWorld()->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_NONE);
	gameLevel->getPhysicsWorld()->setSpeed(2.0f);
	gameLevel->scheduleUpdate();
	gameLevel->addEventListener();

	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	Size finalSize;
	finalSize.width = visibleSize.width + 50;
	finalSize.height = visibleSize.height / GROUND_PERCENTAGE_FOR_BOX;

	PhysicsBody* edgeBody = PhysicsBody::createEdgeBox(finalSize, PhysicsMaterial(0.1f, 0.0f, 0.5f), 3);
	Node* edgeNode = Node::create();
	edgeNode->setPosition(Point(visibleSize.width / 2 + origin.x + 25, origin.y));
	edgeNode->setPhysicsBody(edgeBody);
	gameLevel->addChild(edgeNode);
	gameLevel->bossMode = false;

	auto contactListener = EventListenerPhysicsContact::create();
	contactListener->onContactBegin = CC_CALLBACK_1(GameLevel::onContactBegin, gameLevel);
	gameLevel->getEventDispatcher()->addEventListenerWithSceneGraphPriority(contactListener, gameLevel);

	//TODO: set according to screen and score table height
	gameLevel->statusBar = UIBar::create("Totolin");
	gameLevel->statusBar->setPosition(180, Director::getInstance()->getWinSize().height - 50);
	gameLevel->statusBar->setScale(0.7);
	gameLevel->addChild(gameLevel->statusBar, 5000);

	return gameLevel;
}

GameLevel* GameLevel::createWithPhysics()
{
	GameLevel *ret = new (std::nothrow) GameLevel();
	if (ret && ret->initWithPhysics())
	{
		ret->autorelease();
		return ret;
	}
	else
	{
		CC_SAFE_DELETE(ret);
		return nullptr;
	}
}

void GameLevel::update(float delta)
{
	updateUI();

	if (bossMode) { return; }

	for (int i = 0; i < objectFactories.size(); i++)
	{
		objectFactories.at(i)->createObject();
	}

	if (this->distance == this->mainCharacter->getDistanceTravelled())
	{
		this->levelBackground->slowlyStop();
		this->mainCharacter->setBossMode(true);
		this->levelBoss->moveIn(Vec2(1100,200));
		this->bossMode = true;
	}

}

void GameLevel::updateUI()
{
	int score = mainCharacter->getScore();
	int HP = mainCharacter->getHealth();

	this->statusBar->setPercent(HP);
	this->statusBar->setScore(score);
}

bool GameLevel::onContactBegin(PhysicsContact& contact)
{
	PhysicsBody *a = contact.getShapeA()->getBody();
	PhysicsBody *b = contact.getShapeB()->getBody();

	// COLLISION CHECKING
	
	/*
		ROCKET + PLAYER
	*/
	if ((ROCKET_COLLISION_BITMASK == a->getCollisionBitmask() && PLAYER_COLLISION_BITMASK == b->getCollisionBitmask()))
	{
		Player* player = dynamic_cast<Player*>(contact.getShapeB()->getBody()->getNode());
		InteractiveObject* rocket = dynamic_cast<InteractiveObject*>(contact.getShapeA()->getBody()->getNode());

		collsionPlayerRocket(player, rocket);
	}
	else if ((PLAYER_COLLISION_BITMASK == a->getCollisionBitmask() && ROCKET_COLLISION_BITMASK == b->getCollisionBitmask()))
	{
		Player* player = dynamic_cast<Player*>(contact.getShapeA()->getBody()->getNode());
		InteractiveObject* rocket = dynamic_cast<InteractiveObject*>(contact.getShapeB()->getBody()->getNode());

		collsionPlayerRocket(player, rocket);
	}
	/*
		BULLET -> ROCKET
	*/
	if ((BULLET_COLLISION_BITMASK == a->getCollisionBitmask() && ROCKET_COLLISION_BITMASK == b->getCollisionBitmask()))
	{
		// Cast objects
		Bullet* bullet= dynamic_cast<Bullet*>(contact.getShapeA()->getBody()->getNode());
		InteractiveObject* rocket = dynamic_cast<InteractiveObject*>(contact.getShapeB()->getBody()->getNode());

		collisionBulletRocket(bullet, rocket);	
	} 
	/*
		BULLET <- ROCKET
	*/
	else if ((BULLET_COLLISION_BITMASK == b->getCollisionBitmask() && ROCKET_COLLISION_BITMASK == a->getCollisionBitmask()))
	{
		// Cast objects
		Bullet* bullet = dynamic_cast<Bullet*>(contact.getShapeB()->getBody()->getNode());
		InteractiveObject* rocket = dynamic_cast<InteractiveObject*>(contact.getShapeA()->getBody()->getNode());

		collisionBulletRocket(bullet, rocket);
	}
	
	/*
		MAILBOX -> BULLET
	*/

	if ((MAILBOX_COLLISION_BITMASK == a->getCollisionBitmask() && BULLET_COLLISION_BITMASK == b->getCollisionBitmask()))
	{
		InteractiveObject* mailbox = dynamic_cast<InteractiveObject*>(contact.getShapeA()->getBody()->getNode());
		Bullet* bullet = dynamic_cast<Bullet*>(contact.getShapeB()->getBody()->getNode());

		collisionBulletMailBox(bullet, mailbox);
	}
	/*
		MAILBOX <- BULLET
	*/
	else if ((MAILBOX_COLLISION_BITMASK == b->getCollisionBitmask() && BULLET_COLLISION_BITMASK == a->getCollisionBitmask()))
	{
		Bullet* bullet = dynamic_cast<Bullet*>(contact.getShapeA()->getBody()->getNode());
		InteractiveObject* mailbox = dynamic_cast<InteractiveObject*>(contact.getShapeB()->getBody()->getNode());

		collisionBulletMailBox(bullet, mailbox);
	}

	/*
		BULLET -> ENEMY CANNON
	*/
	if ((BOSS_CANNON_COLLISION_BITMASK == a->getCollisionBitmask() && BULLET_COLLISION_BITMASK == b->getCollisionBitmask()))
	{
		BossCannon* cannon = dynamic_cast<BossCannon*>(contact.getShapeA()->getBody()->getNode());
		Bullet* bullet = dynamic_cast<Bullet*>(contact.getShapeB()->getBody()->getNode());
	
		collisionBulletEnemyCannon(bullet, cannon);
	}
	else if ((BOSS_CANNON_COLLISION_BITMASK == b->getCollisionBitmask() && BULLET_COLLISION_BITMASK == a->getCollisionBitmask()))
	{
		BossCannon* cannon = dynamic_cast<BossCannon*>(contact.getShapeB()->getBody()->getNode());
		Bullet* bullet = dynamic_cast<Bullet*>(contact.getShapeA()->getBody()->getNode());
		
		collisionBulletEnemyCannon(bullet, cannon);
	}

	// MAILBOX -> ROCKET
	if ((MAILBOX_COLLISION_BITMASK == a->getCollisionBitmask() && ROCKET_COLLISION_BITMASK == b->getCollisionBitmask()))
	{
		InteractiveObject* mailbox = dynamic_cast<InteractiveObject*>(contact.getShapeA()->getBody()->getNode());
		InteractiveObject* rocket = dynamic_cast<InteractiveObject*>(contact.getShapeB()->getBody()->getNode());

		collisionMailBoxRocket(mailbox, rocket);
	}
	else if (MAILBOX_COLLISION_BITMASK == b->getCollisionBitmask() && ROCKET_COLLISION_BITMASK == a->getCollisionBitmask())
	{
		InteractiveObject* mailbox = dynamic_cast<InteractiveObject*>(contact.getShapeB()->getBody()->getNode());
		InteractiveObject* rocket = dynamic_cast<InteractiveObject*>(contact.getShapeA()->getBody()->getNode());

		collisionMailBoxRocket(mailbox, rocket);
	}


	if ((MAILBOX_COLLISION_BITMASK == a->getCollisionBitmask() && MAILBOX_COLLISION_BITMASK == b->getCollisionBitmask()))
	{
		InteractiveObject* mailbox1 = dynamic_cast<InteractiveObject*>(contact.getShapeA()->getBody()->getNode());
		InteractiveObject* mailbox2 = dynamic_cast<InteractiveObject*>(contact.getShapeB()->getBody()->getNode());
	
		Vec2 v1 = mailbox1->getPhysicsBody()->getVelocity();
		Vec2 v2 = mailbox2->getPhysicsBody()->getVelocity();

		if (!(v1.x > -1 && v1.x < 1 && v2.x > -1 && v2.x < 1))
			return false;
	}


	return true;
}

void GameLevel::collisionBulletRocket(Bullet* bullet, InteractiveObject* rocket)
{
	// Create explosion
	Vec2 rocketPosition = rocket->getPosition();
	auto explosion = ParticleSun::create();
	explosion->setDuration(0);
	explosion->setPosition(rocketPosition);
	explosion->setScale(2);
	this->addChild(explosion, 1000);

	// Remove from the scene
	bullet->removeFromParentAndCleanup(true);
	rocket->removeFromParentAndCleanup(true);

	// Update score
	this->mainCharacter->addScore(ROCKET_KILL_POINTS);

	// Log a message
	CCLOG("COLLISION BULLET <=> ROCKET");
}

void GameLevel::collisionBulletMailBox(Bullet* bullet, InteractiveObject* mailbox)
{
	mailbox->isHit();
	this->mainCharacter->addScore(MAILBOX_KILL_POINTS);

	bullet->removeFromParentAndCleanup(true);

	CCLOG("COLLISION BULLET <=> MAILBOX");
}

void GameLevel::collisionBulletEnemyCannon(Bullet* bullet, BossCannon* cannon)
{
	cannon->reduceHP(25);
	this->mainCharacter->addScore(MAILBOX_KILL_POINTS);

	// Create explosion
	Vec2 rocketPosition = bullet->getPosition();
	rocketPosition.x += bullet->getBoundingBox().size.width / 2;
	auto explosion = ParticleSun::create();
	explosion->setDuration(0);
	explosion->setScale(2);
	explosion->setPosition(rocketPosition);
	this->addChild(explosion, 1000);

	bullet->removeFromParentAndCleanup(true);
}

void GameLevel::collisionMailBoxRocket(InteractiveObject* mailbox, InteractiveObject* rocket)
{
	// Add score
	this->mainCharacter->addScore(MAILBOX_KILL_POINTS);

	// Create explosion
	Vec2 rocketPosition = rocket->getPosition();
	auto explosion = ParticleSun::create();
	explosion->setDuration(0);
	explosion->setScale(2);
	explosion->setPosition(rocketPosition);
	this->addChild(explosion, 1000);

	rocket->removeFromParentAndCleanup(true);
	mailbox->removeFromParentAndCleanup(true);
}

void GameLevel::collsionPlayerRocket(Player* player, InteractiveObject* rocket)
{
	// Log event
	CCLOG("COLLISION PLAYER <=> ROCKET");

	// Player is hit
	this->mainCharacter->isHit();

	// Create explosion
	Vec2 rocketPosition = rocket->getPosition();
	auto explosion = ParticleSun::create();
	explosion->setDuration(0);
	explosion->setScale(2);
	explosion->setPosition(rocketPosition);
	this->addChild(explosion, 1000);

	// Remove rocket
	rocket->removeFromParentAndCleanup(true);
}


void GameLevel::addEventListener()
{
	// Create keyboard mapping
	auto eventListener = EventListenerKeyboard::create();
	Director::getInstance()->getOpenGLView()->setIMEKeyboardState(true);

	// Set events on press and release
	eventListener->onKeyPressed = [=](EventKeyboard::KeyCode keyCode, Event* event){
		if (keys.find(keyCode) == keys.end()){
			keys[keyCode] = std::chrono::high_resolution_clock::now();
		}
		switch (keyCode){
		case EventKeyboard::KeyCode::KEY_P:
			this->togglePhysicsWorld();
			break;
		default:
			break;
		}
	};

	// Set mapping
	eventListener->onKeyReleased = [=](EventKeyboard::KeyCode keyCode, Event* event){
		keys.erase(keyCode);
	};

	// Set listener
	this->_eventDispatcher->addEventListenerWithSceneGraphPriority(eventListener, this);
}

void GameLevel::togglePhysicsWorld()
{
	if (this->getPhysicsWorld()->getDebugDrawMask() == PhysicsWorld::DEBUGDRAW_ALL)
	{
		this->getPhysicsWorld()->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_NONE);
	}
	else
	{
		this->getPhysicsWorld()->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_ALL);
	}
}
