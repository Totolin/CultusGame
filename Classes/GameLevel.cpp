#include "GameLevel.h"
#include "UIBar.h"
#include "proj.win32\BossCannon.h"

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
	gameLevel->getPhysicsWorld()->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_ALL);
	gameLevel->getPhysicsWorld()->setSpeed(2.0f);
	gameLevel->scheduleUpdate();

	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	Size finalSize;
	finalSize.width = visibleSize.width + 20;
	finalSize.height = visibleSize.height / GROUND_PERCENTAGE_FOR_BOX;

	PhysicsBody* edgeBody = PhysicsBody::createEdgeBox(finalSize, PhysicsMaterial(0.1f, 0.0f, 0.5f), 3);
	Node* edgeNode = Node::create();
	edgeNode->setPosition(Point(visibleSize.width / 2 + origin.x + 20, origin.y));
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
	if ((ROCKET_COLLISION_BITMASK == a->getCollisionBitmask() && PLAYER_COLLISION_BITMASK == b->getCollisionBitmask()) || (PLAYER_COLLISION_BITMASK == a->getCollisionBitmask() && ROCKET_COLLISION_BITMASK == b->getCollisionBitmask()))
	{
		CCLOG("COLLISION HAS OCCURED WITH PLAYER");
		this->mainCharacter->isHit();
	}

	/*
		BULLET -> ROCKET
	*/
	if ((BULLET_COLLISION_BITMASK == a->getCollisionBitmask() && ROCKET_COLLISION_BITMASK == b->getCollisionBitmask()))
	{
		// Cast objects
		Bullet* bullet= dynamic_cast<Bullet*>(contact.getShapeA()->getBody()->getNode());
		InteractiveObject* rocket = dynamic_cast<InteractiveObject*>(contact.getShapeB()->getBody()->getNode());

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

		// Log a message
		CCLOG("COLLISION HAS OCCURED WITH BULLET");

		// Update score
		this->mainCharacter->addScore(ROCKET_KILL_POINTS);
		
	} 
	/*
		BULLET <- ROCKET
	*/
	else if ((BULLET_COLLISION_BITMASK == b->getCollisionBitmask() && ROCKET_COLLISION_BITMASK == a->getCollisionBitmask()))
	{
		// Cast objects
		Bullet* bullet = dynamic_cast<Bullet*>(contact.getShapeB()->getBody()->getNode());
		InteractiveObject* rocket = dynamic_cast<InteractiveObject*>(contact.getShapeA()->getBody()->getNode());

		// Create explosion
		Vec2 rocketPosition = rocket->getPosition();
		auto explosion = ParticleSun::create();
		explosion->setDuration(0);
		explosion->setScale(2);
		explosion->setPosition(rocketPosition);
		this->addChild(explosion, 1000);


		// Remove from the scene
		bullet->removeFromParentAndCleanup(true);
		rocket->removeFromParentAndCleanup(true);

		// Log a message
		CCLOG("COLLISION HAS OCCURED WITH BULLET");

		// Update score
		this->mainCharacter->addScore(ROCKET_KILL_POINTS);
	}
	
	/*
		MAILBOX -> BULLET
	*/

	if ((MAILBOX_COLLISION_BITMASK == a->getCollisionBitmask() && BULLET_COLLISION_BITMASK == b->getCollisionBitmask()))
	{
		InteractiveObject* object = dynamic_cast<InteractiveObject*>(contact.getShapeA()->getBody()->getNode());
		Bullet* bullet = dynamic_cast<Bullet*>(contact.getShapeB()->getBody()->getNode());
		object->isHit();
		this->mainCharacter->addScore(MAILBOX_KILL_POINTS);

		// Create spark
		//auto spark = ParticleSystemQuad::create("spark.plist");
		//Size bulletSize = bullet->getBoundingBox().size;
		//spark->setPosition(bullet->getPositionX() + bulletSize.width / 2, bullet->getPositionY());
		//spark->setDuration(1);
		//spark->setScale(2);
		//this->addChild(spark, 1000);


		bullet->removeFromParentAndCleanup(true);


		CCLOG("COLLISION MAILBOX = A");

	}
	/*
		MAILBOX <- BULLET
	*/
	else if ((MAILBOX_COLLISION_BITMASK == b->getCollisionBitmask() && BULLET_COLLISION_BITMASK == a->getCollisionBitmask()))
	{
		Bullet* bullet = dynamic_cast<Bullet*>(contact.getShapeA()->getBody()->getNode());
		InteractiveObject* object = dynamic_cast<InteractiveObject*>(contact.getShapeB()->getBody()->getNode());
		object->isHit();
		this->mainCharacter->addScore(MAILBOX_KILL_POINTS);

		// Create spark
		//auto spark = ParticleSystemQuad::create("spark.plist");
		//Size bulletSize = bullet->getBoundingBox().size;
		//spark->setPosition(bullet->getPositionX() + bulletSize.width / 2, bullet->getPositionY());
		//spark->setDuration(1);
		//spark->setScale(2);
		//this->addChild(spark, 1000);


		bullet->removeFromParentAndCleanup(true);

		CCLOG("COLLISION MAILBOX = B");
	}

	/*
		BULLET -> ENEMY CANNON
	*/
	if ((BOSS_CANNON_COLLISION_BITMASK == a->getCollisionBitmask() && BULLET_COLLISION_BITMASK == b->getCollisionBitmask()))
	{
		BossCannon* cannon = dynamic_cast<BossCannon*>(contact.getShapeA()->getBody()->getNode());
		Bullet* bullet = dynamic_cast<Bullet*>(contact.getShapeB()->getBody()->getNode());
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
	else if ((BOSS_CANNON_COLLISION_BITMASK == b->getCollisionBitmask() && BULLET_COLLISION_BITMASK == a->getCollisionBitmask()))
	{
		BossCannon* cannon = dynamic_cast<BossCannon*>(contact.getShapeB()->getBody()->getNode());
		Bullet* bullet = dynamic_cast<Bullet*>(contact.getShapeA()->getBody()->getNode());
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
	return true;
}