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


	gameLevel->scoreLabel = Label::createWithTTF("Score: 0", "font.ttf", 15);
	gameLevel->scoreLabel->setPosition(70, Director::getInstance()->getWinSize().height - 20);
	gameLevel->setScoreLabel(gameLevel->scoreLabel);

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

	gameLevel->loadingBar = LoadingBar::create("loadingbar.png");
	gameLevel->loadingBar->setDirection(LoadingBar::Direction::RIGHT);
	gameLevel->loadingBar->setPercent(100);
	gameLevel->loadingBar->setColor(Color3B::GREEN);
	gameLevel->loadingBar->setPosition(Vec2(120, Director::getInstance()->getWinSize().height - 50));
	gameLevel->addChild(gameLevel->loadingBar,500);

	auto contactListener = EventListenerPhysicsContact::create();
	contactListener->onContactBegin = CC_CALLBACK_1(GameLevel::onContactBegin, gameLevel);
	gameLevel->getEventDispatcher()->addEventListenerWithSceneGraphPriority(contactListener, gameLevel);


	UIBar* bar = UIBar::create("Geo");
	bar->setPosition(500, 200);
	gameLevel->addChild(bar, 5000);

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

	updateScore();
	

}

void GameLevel::updateScore()
{
	int score = mainCharacter->getScore();

	this->scoreLabel->setString("Score: " + to_string(score));
}

void GameLevel::setScoreLabel(Label* label)
{
	this->scoreLabel = label;
	this->addChild(label,100);
}

bool GameLevel::onContactBegin(PhysicsContact& contact)
{
	PhysicsBody *a = contact.getShapeA()->getBody();
	PhysicsBody *b = contact.getShapeB()->getBody();

	// check if the bodies have collided
	
	if ((ROCKET_COLLISION_BITMASK == a->getCollisionBitmask() && PLAYER_COLLISION_BITMASK == b->getCollisionBitmask()) || (PLAYER_COLLISION_BITMASK == a->getCollisionBitmask() && ROCKET_COLLISION_BITMASK == b->getCollisionBitmask()))
	{
		CCLOG("COLLISION HAS OCCURED WITH PLAYER");
	}

	if ((ROCKET_COLLISION_BITMASK == a->getCollisionBitmask() && BULLET_COLLISION_BITMASK == b->getCollisionBitmask()) || (BULLET_COLLISION_BITMASK == a->getCollisionBitmask() && ROCKET_COLLISION_BITMASK == b->getCollisionBitmask()))
	{
		CCLOG("COLLISION HAS OCCURED WITH BULLET");
	}
	
	if ((MAILBOX_COLLISION_BITMASK == a->getCollisionBitmask() && BULLET_COLLISION_BITMASK == b->getCollisionBitmask()))
	{
		InteractiveObject* object = dynamic_cast<InteractiveObject*>(contact.getShapeA()->getBody()->getNode());
		object->isHit();
		CCLOG("COLLISION MAILBOX = A");
	}
	else if ((MAILBOX_COLLISION_BITMASK == b->getCollisionBitmask() && BULLET_COLLISION_BITMASK == a->getCollisionBitmask()))
	{
		InteractiveObject* object = dynamic_cast<InteractiveObject*>(contact.getShapeB()->getBody()->getNode());
		object->isHit();
		CCLOG("COLLISION MAILBOX = B");
	}

	return true;
}