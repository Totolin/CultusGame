#include "GameLevel.h"
#include "UIBar.h"

GameLevel::GameLevel()
{
}

GameLevel::~GameLevel()
{
}

void GameLevel::setBoss(Boss* levelBoss)
{
	this->levelBoss = levelBoss;
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
	this->addChild(objectFactory);
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

	auto contactListener = EventListenerPhysicsContact::create();
	contactListener->onContactBegin = CC_CALLBACK_1(GameLevel::onContactBegin, gameLevel);
	gameLevel->getEventDispatcher()->addEventListenerWithSceneGraphPriority(contactListener, gameLevel);

	//TODO: set according to screen and score table height
	gameLevel->statusBar = UIBar::create("Totolin");
	gameLevel->statusBar->setPosition(180, Director::getInstance()->getWinSize().height - 100);
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
	for (int i = 0; i < objectFactories.size(); i++)
	{
		objectFactories.at(i)->createObject();
	}


	if (this->distance == this->mainCharacter->getDistanceTravelled())
	{
		this->levelBackground->slowlyStop();
		this->mainCharacter->setBossMode(true);
	}

	updateUI();
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

	// check if the bodies have collided
	
	if ((ROCKET_COLLISION_BITMASK == a->getCollisionBitmask() && PLAYER_COLLISION_BITMASK == b->getCollisionBitmask()) || (PLAYER_COLLISION_BITMASK == a->getCollisionBitmask() && ROCKET_COLLISION_BITMASK == b->getCollisionBitmask()))
	{
		CCLOG("COLLISION HAS OCCURED WITH PLAYER");
		this->mainCharacter->isHit();
	}

	if ((BULLET_COLLISION_BITMASK == a->getCollisionBitmask() && ROCKET_COLLISION_BITMASK == b->getCollisionBitmask()))
	{
		// Cast objects
		Bullet* bullet= dynamic_cast<Bullet*>(contact.getShapeA()->getBody()->getNode());
		InteractiveObject* rocket = dynamic_cast<InteractiveObject*>(contact.getShapeB()->getBody()->getNode());

		// Create explosion
		Vec2 rocketPosition = rocket->getPosition();
		auto explosion = ParticleSystemQuad::create("explosion.plist");
		explosion->setDuration(1);
		explosion->setPosition(rocketPosition);
		this->addChild(explosion,1000);

		// Remove from the scene
		bullet->removeFromParentAndCleanup(true);
		rocket->removeFromParentAndCleanup(true);

		// Log a message
		CCLOG("COLLISION HAS OCCURED WITH BULLET");

		// Update score
		this->mainCharacter->addScore(ROCKET_KILL_POINTS);
		
	} else if ((BULLET_COLLISION_BITMASK == b->getCollisionBitmask() && ROCKET_COLLISION_BITMASK == a->getCollisionBitmask()))
	{
		// Cast objects
		Bullet* bullet = dynamic_cast<Bullet*>(contact.getShapeB()->getBody()->getNode());
		InteractiveObject* rocket = dynamic_cast<InteractiveObject*>(contact.getShapeA()->getBody()->getNode());

		// Create explosion
		Vec2 rocketPosition = rocket->getPosition();
		auto explosion = ParticleSystemQuad::create("explosion.plist");
		explosion->setPosition(rocketPosition);
		explosion->setDuration(1);

		this->addChild(explosion, 1000);

		// Remove from the scene
		bullet->removeFromParentAndCleanup(true);
		rocket->removeFromParentAndCleanup(true);

		// Log a message
		CCLOG("COLLISION HAS OCCURED WITH BULLET");

		// Update score
		this->mainCharacter->addScore(ROCKET_KILL_POINTS);
	}
	
	if ((MAILBOX_COLLISION_BITMASK == a->getCollisionBitmask() && BULLET_COLLISION_BITMASK == b->getCollisionBitmask()))
	{
		InteractiveObject* object = dynamic_cast<InteractiveObject*>(contact.getShapeA()->getBody()->getNode());
		object->isHit();
		this->mainCharacter->addScore(MAILBOX_KILL_POINTS);
		CCLOG("COLLISION MAILBOX = A");

	}else if ((MAILBOX_COLLISION_BITMASK == b->getCollisionBitmask() && BULLET_COLLISION_BITMASK == a->getCollisionBitmask()))
	{
		InteractiveObject* object = dynamic_cast<InteractiveObject*>(contact.getShapeB()->getBody()->getNode());
		object->isHit();
		this->mainCharacter->addScore(MAILBOX_KILL_POINTS);
		CCLOG("COLLISION MAILBOX = B");
	}

	return true;
}