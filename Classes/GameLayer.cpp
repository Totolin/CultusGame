#include "GameLayer.h"
#include "UIBar.h"
#include "BossCannon.h"
#include "BossBullet.h"
#include "GameLevel.h"


GameLayer::GameLayer()
{
}

GameLayer::~GameLayer()
{
}

Player* GameLayer::getMainCharacter()
{
	return mainCharacter;
}

void GameLayer::setBoss(Boss* levelBoss)
{
	this->levelBoss = levelBoss;
	this->addChild(levelBoss);
}

void GameLayer::setBackground(ParallaxBackground* levelBackground)
{
	this->levelBackground = levelBackground;
	this->addChild(levelBackground);
}

void GameLayer::setPlayer(Player* mainCharacter)
{
	this->mainCharacter = mainCharacter;
	this->addChild(mainCharacter,1000);
}

void GameLayer::setDistanceToBoss(long long distance)
{
	this->distance = distance;
}


void GameLayer::addObjectFactory(InteractiveObjectFactory* objectFactory)
{
	this->objectFactories.push_back(objectFactory);
}

GameLayer* GameLayer::create()
{
	GameLayer* gameLayer = new GameLayer();
	gameLayer->scheduleUpdate();

	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	Size finalSize;
	finalSize.width = visibleSize.width + 200;
	finalSize.height = visibleSize.height / GROUND_PERCENTAGE_FOR_BOX;

	PhysicsBody* edgeBody = PhysicsBody::createEdgeBox(finalSize, PhysicsMaterial(1000.0f, 0.0f, 0.5f), 3);
	Node* edgeNode = Node::create();
	edgeNode->setPosition(Point(visibleSize.width / 2 + origin.x + 100, origin.y));
	edgeBody->setCollisionBitmask(GROUND_COLLISION_BITMASK);
	edgeBody->setContactTestBitmask(true);
	edgeNode->setPhysicsBody(edgeBody);

	gameLayer->addChild(edgeNode);

	gameLayer->bossMode = false;

	auto contactListener = EventListenerPhysicsContact::create();
	contactListener->onContactBegin = CC_CALLBACK_1(GameLayer::onContactBegin, gameLayer);
	gameLayer->getEventDispatcher()->addEventListenerWithSceneGraphPriority(contactListener, gameLayer);

	//TODO: set according to screen and score table height
	gameLayer->statusBar = UIBar::create("Geo");
	gameLayer->statusBar->setScale(0.7);
	gameLayer->statusBar->setPosition(180, Director::getInstance()->getWinSize().height - 50);
	gameLayer->addChild(gameLayer->statusBar, 5000);

	return gameLayer;
}


void GameLayer::update(float delta)
{
	updateUI();
	this->levelBoss->updatePlayerPosition(this->mainCharacter->getPosition());

	// Check if the main character is dead
	if (mainCharacter->getHealth() <= 0 || mainCharacter->getPosition().y < 0)
	{
		// Kill it with fire
		mainCharacter->isDead();

		// Display a GAME OVER screen
		GameLevel* gameLevel = dynamic_cast<GameLevel*>(Director::getInstance()->getRunningScene());

		gameLevel->gameOver();
	}

	if (bossMode) { return; }

	for (int i = 0; i < objectFactories.size(); i++)
	{
		objectFactories.at(i)->createObject();
	}

	if (this->distance == this->mainCharacter->getDistanceTravelled())
	{
		this->levelBackground->slowlyStop();
		this->mainCharacter->setBossMode(true);
		this->levelBoss->moveIn(Vec2(Director::getInstance()->getWinSize().width
			,(Director::getInstance()->getWinSize().height / GROUND_PERCENTAGE_FOR_BOX / 2) + levelBoss->getBoundingBox().size.height / 2));
		this->bossMode = true;
	}
}

void GameLayer::updateUI()
{
	int score = mainCharacter->getScore();
	int HP = mainCharacter->getHealth();

	this->statusBar->setPercent(HP);
	this->statusBar->setScore(score);
}

bool GameLayer::onContactBegin(PhysicsContact& contact)
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

	if (PLAYER_COLLISION_BITMASK == a->getCollisionBitmask() && SPIKES_COLLISION_BITMASK == b->getCollisionBitmask())
	{
		InteractiveObject* hole = dynamic_cast<InteractiveObject*>(contact.getShapeB()->getBody()->getNode());
		collsionPlayerSpike(mainCharacter, hole);
		return false;
	}
	else if (PLAYER_COLLISION_BITMASK == b->getCollisionBitmask() && SPIKES_COLLISION_BITMASK == a->getCollisionBitmask())
	{
		InteractiveObject* hole = dynamic_cast<InteractiveObject*>(contact.getShapeA()->getBody()->getNode());
		collsionPlayerSpike(mainCharacter, hole);
		return false;
	}

	if (BOSSBULLET_COLLISION_BITMASK == a->getCollisionBitmask() && GROUND_COLLISION_BITMASK == b->getCollisionBitmask() ){
		BossBullet* bullet = dynamic_cast<BossBullet*>(contact.getShapeA()->getBody()->getNode());

		return collisionBossBulletGround(bullet);

	}
	else if (BOSSBULLET_COLLISION_BITMASK == b->getCollisionBitmask() && GROUND_COLLISION_BITMASK == a->getCollisionBitmask())
	{
		BossBullet* bullet = dynamic_cast<BossBullet*>(contact.getShapeB()->getBody()->getNode());

		return collisionBossBulletGround(bullet);

	}

	
	if (BOSSBULLET_COLLISION_BITMASK == a->getCollisionBitmask() && PLAYER_COLLISION_BITMASK == b->getCollisionBitmask())
	{
		Player* player = dynamic_cast<Player*>(contact.getShapeB()->getBody()->getNode());
		BossBullet* bullet = dynamic_cast<BossBullet*>(contact.getShapeA()->getBody()->getNode());


		return collisionPlayerBossBulet(player, bullet);
	}
	else if (BOSSBULLET_COLLISION_BITMASK == b->getCollisionBitmask() && PLAYER_COLLISION_BITMASK == a->getCollisionBitmask())
	{
		Player* player = dynamic_cast<Player*>(contact.getShapeA()->getBody()->getNode());
		BossBullet* bullet = dynamic_cast<BossBullet*>(contact.getShapeB()->getBody()->getNode());

		
		return collisionPlayerBossBulet(player, bullet);
	}

	
	if ((BULLET_COLLISION_BITMASK == a->getCollisionBitmask() && BOSSBULLET_COLLISION_BITMASK == b->getCollisionBitmask()))
	{
		// Cast objects
		Bullet* bullet = dynamic_cast<Bullet*>(contact.getShapeA()->getBody()->getNode());
		BossBullet* bossBullet = dynamic_cast<BossBullet*>(contact.getShapeB()->getBody()->getNode());

		collisionBulletBossBullet(bullet, bossBullet);
	}
	else if ((BULLET_COLLISION_BITMASK == b->getCollisionBitmask() && BOSSBULLET_COLLISION_BITMASK == a->getCollisionBitmask()))
	{
		// Cast objects
		Bullet* bullet = dynamic_cast<Bullet*>(contact.getShapeB()->getBody()->getNode());
		BossBullet* bossBullet = dynamic_cast<BossBullet*>(contact.getShapeA()->getBody()->getNode());

		collisionBulletBossBullet(bullet, bossBullet);
	}

	if (MAILBOX_COLLISION_BITMASK == a->getCollisionBitmask() && SPIKES_COLLISION_BITMASK == b->getCollisionBitmask())
	{
		InteractiveObject* mailbox = dynamic_cast<InteractiveObject*>(contact.getShapeA()->getBody()->getNode());
		InteractiveObject* spike = dynamic_cast<InteractiveObject*>(contact.getShapeB()->getBody()->getNode());

		collisionMailBoxSpike(mailbox, spike);
	}
	else if (MAILBOX_COLLISION_BITMASK == b->getCollisionBitmask() && SPIKES_COLLISION_BITMASK == a->getCollisionBitmask())
	{
		InteractiveObject* mailbox = dynamic_cast<InteractiveObject*>(contact.getShapeB()->getBody()->getNode());
		InteractiveObject* spike = dynamic_cast<InteractiveObject*>(contact.getShapeA()->getBody()->getNode());

		collisionMailBoxSpike(mailbox, spike);
	}


	if (MAILBOX_COLLISION_BITMASK == a->getCollisionBitmask() && MAILBOX_COLLISION_BITMASK == b->getCollisionBitmask())
	{
		InteractiveObject* mailbox1 = dynamic_cast<InteractiveObject*>(contact.getShapeA()->getBody()->getNode());
		InteractiveObject* mailbox2 = dynamic_cast<InteractiveObject*>(contact.getShapeB()->getBody()->getNode());


		collisionMailBoxMailBox(mailbox1, mailbox2);
	}

	if (SPIKES_COLLISION_BITMASK == a->getCollisionBitmask() && SPIKES_COLLISION_BITMASK == b->getCollisionBitmask())
	{
		InteractiveObject* spike1 = dynamic_cast<InteractiveObject*>(contact.getShapeA()->getBody()->getNode());
		InteractiveObject* spike2 = dynamic_cast<InteractiveObject*>(contact.getShapeB()->getBody()->getNode());


		collsionSpikeSpike(spike1, spike2);
	}

	return true;
}

void GameLayer::collisionBulletRocket(Bullet* bullet, InteractiveObject* rocket)
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

void GameLayer::collisionBulletMailBox(Bullet* bullet, InteractiveObject* mailbox)
{
	mailbox->isHit();
	this->mainCharacter->addScore(MAILBOX_KILL_POINTS);

	bullet->removeFromParentAndCleanup(true);

	CCLOG("COLLISION BULLET <=> MAILBOX");
}

void GameLayer::collsionPlayerSpike(Player* player, InteractiveObject* hole)
{
	// Log event
	CCLOG("COLLISION PLAYER <=> SPIKES");

	// Player is hit
	this->mainCharacter->isHit();
}

void GameLayer::collisionMailBoxSpike(InteractiveObject* mailbox, InteractiveObject* spike)
{
	if (mailbox == nullptr)
		return;
	mailbox->removeFromParentAndCleanup(true);
}

void GameLayer::collisionMailBoxMailBox(InteractiveObject* mailbox1, InteractiveObject* mailbox2)
{
	if (mailbox1 == nullptr || mailbox2 == nullptr)
		return;
	
	if (mailbox1->getPositionY() > mailbox2->getPositionY())
		mailbox2->removeFromParentAndCleanup(true);
	else
		mailbox1->removeFromParentAndCleanup(true);

}

void GameLayer::collsionSpikeSpike(InteractiveObject* spike1, InteractiveObject* spike2)
{
	if (spike1 == nullptr || spike2 == nullptr)
		return;

	if (spike1->getPositionY() > spike2->getPositionY())
		spike2->removeFromParentAndCleanup(true);
	else
		spike1->removeFromParentAndCleanup(true);
}

void GameLayer::collisionBulletEnemyCannon(Bullet* bullet, BossCannon* cannon)
{
	cannon->reduceHP(25);
	this->mainCharacter->addScore(MAILBOX_KILL_POINTS);

	if (bullet == nullptr)
		return;

	// Create explosion
	Vec2 rocketPosition = bullet->getPosition();
	rocketPosition.x += bullet->getBoundingBox().size.width / 2;
	bullet->removeFromParentAndCleanup(true);

	auto explosion = ParticleSun::create();
	explosion->setDuration(0);
	explosion->setScale(2);
	explosion->setPosition(rocketPosition);
	this->addChild(explosion, 1000);

}

void GameLayer::collisionMailBoxRocket(InteractiveObject* mailbox, InteractiveObject* rocket)
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

void GameLayer::collsionPlayerRocket(Player* player, InteractiveObject* rocket)
{
	if (rocket == nullptr)
		return;
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


bool GameLayer::collisionPlayerBossBulet(Player* player, BossBullet* bossBullet)
{
	if (player->isInvurnerable())
		return false;
	if (bossBullet == nullptr)
		return false;

	player->isHit();
	
 	bossBullet->removeFromParentAndCleanup(true);
	return true;
}

bool GameLayer::collisionBossBulletGround(BossBullet* bossBullet)
{
	if (bossBullet == nullptr) { return false; }
	if (!bossBullet->getExplodeOnGround())
		return false;

	// Create explosion
	Vec2 rocketPosition = bossBullet->getPosition();
	rocketPosition.y -= bossBullet->getBoundingBox().size.height / 2;

	auto explosion = ParticleSun::create();
	explosion->setDuration(0);
	explosion->setPosition(rocketPosition);
	explosion->setScale(2);
	this->addChild(explosion, 1000);

	bossBullet->removeFromParentAndCleanup(true);

	return true;

}

void GameLayer::collisionBulletBossBullet(Bullet* bullet, BossBullet* bossBullet)
{

	if (bullet == nullptr || bossBullet == nullptr)
	{
		return;
	}


	// Create explosion
  	Vec2 rocketPosition = bossBullet->getPosition();
	auto explosion = ParticleSun::create();
	explosion->setDuration(0);
	explosion->setPosition(rocketPosition);
	explosion->setScale(2);
	this->addChild(explosion, 1000);

	// Remove from the scene
	bullet->removeFromParentAndCleanup(true);
	bossBullet->removeFromParentAndCleanup(true);

	// Update score
	this->mainCharacter->addScore(ROCKET_KILL_POINTS);
}