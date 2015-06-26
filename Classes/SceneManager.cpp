#include "SceneManager.h"
#include "ParallaxBackground.h"
#include "IntermediaryScene.h"
#include "GameLayer.h"
#include "GameLevel.h"

SceneManager::SceneManager()
{
}

SceneManager::~SceneManager()
{

}

SceneManager& SceneManager::getInstance()
{
	static SceneManager instance;
	return instance;
}

void SceneManager::addSceneToMainStack(Scene* newScene)
{
	mainStack.pushBack(newScene);
}

void SceneManager::fillStack()
{
	// Get instance of director
	Director* director = Director::getInstance();

	// Empty the stack
	director->popToRootScene();

	// Add scenes to stack
	//director->pushScene(generateLevel(3));
	//director->pushScene(generateLevel(2));
	director->replaceScene(generateLevel(2));
}

Scene* SceneManager::generateLevel(int levelIndex)
{
	if (levelIndex == 0) {
		Director* director = Director::getInstance();

		float height = director->getWinSize().height;
		float width = director->getWinSize().width;

		// Create start scene
		ParallaxBackground* bckMenu = new ParallaxBackground();
		bckMenu->addImage("night.png", Vec2(width / 2, height / 1.3), Vec2(0.05, 0));
		bckMenu->addImage("city.png", Vec2(width / 2, height / 1.6), Vec2(0.3, 0));
		bckMenu->addImage("street.png", Vec2(width / 2, height / 2.6), Vec2(1.0, 0), true);
		bckMenu->scheduleUpdate();

		auto startScene = IntermediaryScene::create(IntermediaryScene::MENU);
		startScene->setBackground(bckMenu);

		// Create dummy player
		auto dummy = DummyPlayer::create();
		dummy->setPosition(Vec2(width / 2, 130));
		startScene->setPlayer(dummy);

		Label* playButtonLabel = Label::createWithTTF("Play", "font.ttf", 35);
		MenuItem* playButton = MenuItemLabel::create(playButtonLabel, [&](Ref* sender){SceneManager::getInstance().fillStack();});

		Label* optionsButtonLabel = Label::createWithTTF("Options", "font.ttf", 35);
		MenuItem* optionsButton = MenuItemLabel::create(optionsButtonLabel);

		Label* exitButtonLabel = Label::createWithTTF("Exit", "font.ttf", 35);
		MenuItem* exitButton = MenuItemLabel::create(exitButtonLabel, [&](Ref* sender){Director::getInstance()->end(); });

		startScene->addMenuItem(playButton);
		startScene->addMenuItem(optionsButton);
		startScene->addMenuItem(exitButton);
		startScene->createMenu();

		return startScene;
	}
	if (levelIndex == 1) {
		Director* director = Director::getInstance();

		// Create a new GameLayer
		GameLayer* firstLevelLayer = GameLayer::create();

		// Create a background
		ParallaxBackground* bckFirstLevel = new ParallaxBackground();

		float height = director->getWinSize().height;
		float width = director->getWinSize().width;

		// Create animations and bullets
		bckFirstLevel->addImage("night.png", Vec2(width / 2, height / 1.3), Vec2(0.05, 0));
		bckFirstLevel->addImage("city.png", Vec2(width / 2, height / 1.6), Vec2(0.3, 0));
		bckFirstLevel->addImage("street.png", Vec2(width / 2, height / 2.6), Vec2(1.0, 0),true);
		bckFirstLevel->scheduleUpdate();

		// Create music
		//CocosDenshion::SimpleAudioEngine* audioEngine = CocosDenshion::SimpleAudioEngine::getInstance();
		//audioEngine->playBackgroundMusic("darude.mp3", true);

		// Create player
		Player* hero = Player::create();
		hero->setPosition(Vec2(width / 2, 130));
		hero->setTag(PLAYER_TAG);

		// Create boss
		Boss* boss = Boss::create(OBJECT_FIRSTBOSS);

		BossCannon* cannon1 = BossCannon::create(OBJECT_FIRSTBOSS_CANNON_1, OBJECT_FIRSTBOSS_CANNON_1_D, OBJECT_BOSSBULLET_LASER);
		cannon1->setPosition(Vec2(70, 100));
		cannon1->setFireMethod(1, 10, 50);

		BossCannon* cannon2 = BossCannon::create(OBJECT_FIRSTBOSS_CANNON_2, OBJECT_FIRSTBOSS_CANNON_2_D, OBJECT_BOSSBULLET_SPIKEBALL);
		cannon2->setPosition(Vec2(50, 50));
		cannon2->setFireMethod(2, 10, 50);

		BossCannon* cannon3 = BossCannon::create(OBJECT_FIRSTBOSS_CANNON_3, OBJECT_FIRSTBOSS_CANNON_3_D, OBJECT_BOSSBULLET_BALL);
		cannon3->setPosition(Vec2(70, 200));
		cannon3->setFireMethod(3, 3, 50);

		boss->addCannon(1, cannon2);
		boss->addCannon(2, cannon1);
		boss->addCannon(3, cannon3);

		// Create Interactive object factory
		InteractiveObjectFactory* mailboxFactory = InteractiveObjectFactory::create(OBJECT_MAILBOX, director->getWinSize().height * 1.6 / 800, false, MAILBOX_COLLISION_BITMASK, true, false, true);
		mailboxFactory->setPositionInterval(Vec2(height / GROUND_PERCENTAGE_FOR_BOX + 10, height / GROUND_PERCENTAGE_FOR_BOX + 10));
		mailboxFactory->setSpawnFrequency(5);
		mailboxFactory->setSpeed(Vec2(-(Director::getInstance()->getWinSize().width * 10.0 / 800), 0));

		InteractiveObjectFactory* rocketFactory = InteractiveObjectFactory::create(OBJECT_ROCKET, director->getWinSize().height * 1.6 / 800, false, ROCKET_COLLISION_BITMASK, true, false, false);
		rocketFactory->setPositionInterval(Vec2(100, height));
		rocketFactory->setSpeed(Vec2(-(Director::getInstance()->getWinSize().width * 25.0 / 800), 0));
		rocketFactory->setSpawnFrequency(20);

		InteractiveObjectFactory* spikesFactory = InteractiveObjectFactory::create(OBJECT_SPIKES, director->getWinSize().height * 0.5 / 800, false, SPIKES_COLLISION_BITMASK, false, true, true);
		spikesFactory->setPositionInterval(Vec2(height / GROUND_PERCENTAGE_FOR_BOX + 10, height / GROUND_PERCENTAGE_FOR_BOX + 10));
		spikesFactory->setSpawnFrequency(5);
		spikesFactory->setSpeed(Vec2(-(Director::getInstance()->getWinSize().width * 10.0 / 800), 0));


		firstLevelLayer->setBackground(bckFirstLevel);
		firstLevelLayer->setPlayer(hero);
		firstLevelLayer->setBoss(boss);
		firstLevelLayer->setDistanceToBoss(100);
		firstLevelLayer->addObjectFactory(mailboxFactory);
		firstLevelLayer->addObjectFactory(rocketFactory);
		firstLevelLayer->addObjectFactory(spikesFactory);

		//Create Scene
		GameLevel* firstLevel = GameLevel::create(firstLevelLayer);

		return firstLevel;
	}
	if (levelIndex == 2)
	{
		Director* director = Director::getInstance();

		// Create a new GameLayer
		GameLayer* secondLevelLayer = GameLayer::create();

		// Create a background
		ParallaxBackground* bckSecondLevel = new ParallaxBackground();

		float height = director->getWinSize().height;
		float width = director->getWinSize().width;

		// Create animations and bullets
		bckSecondLevel->addImage("night.png", Vec2(width / 2, height / 1.3), Vec2(0.05, 0));
		bckSecondLevel->addImage("city.png", Vec2(width / 2, height / 1.6), Vec2(0.3, 0));
		bckSecondLevel->addImage("street.png", Vec2(width / 2, height / 2.6), Vec2(1.0, 0), true);
		bckSecondLevel->scheduleUpdate();

		// Create music
		//CocosDenshion::SimpleAudioEngine* audioEngine = CocosDenshion::SimpleAudioEngine::getInstance();
		//audioEngine->playBackgroundMusic("darude.mp3", true);

		// Create player
		Player* hero = Player::create();
		hero->setPosition(Vec2(width / 2, 130));
		hero->setTag(PLAYER_TAG);

		// Create boss
		Boss* boss = Boss::create(OBJECT_SECONDBOSS,true);

		BossCannon* cannon1 = BossCannon::create(OBJECT_SECONDBOSS_CANNON_1, OBJECT_SECONDBOSS_CANNON_1_D, OBJECT_BOSSBULLET_ENERGYBALL);
		cannon1->setPosition(Vec2(70, 100));
		cannon1->setFireMethod(1, 10, 50);

		BossCannon* cannon2 = BossCannon::create(OBJECT_SECONDBOSS_CANNON_2, OBJECT_SECONDBOSS_CANNON_2_D, OBJECT_BOSSBULLET_SAWBLADE);
		cannon2->setPosition(Vec2(50, 50));
		cannon2->setFireMethod(2, 10, 50);

		BossCannon* cannon3 = BossCannon::create(OBJECT_SECONDBOSS_CANNON_3, OBJECT_SECONDBOSS_CANNON_3_D, OBJECT_BOSSBULLET_FLAMEBALL);
		cannon3->setPosition(Vec2(70, 200));
		cannon3->setFireMethod(3, 3, 50);

		boss->addCannon(1, cannon1);
		boss->addCannon(2, cannon2);
		boss->addCannon(3, cannon3);

		// Create Interactive object factory
		InteractiveObjectFactory* mailboxFactory = InteractiveObjectFactory::create(OBJECT_MAILBOX, director->getWinSize().height * 1.6 / 800, false, MAILBOX_COLLISION_BITMASK, true, false, true);
		mailboxFactory->setPositionInterval(Vec2(height / GROUND_PERCENTAGE_FOR_BOX + 10, height / GROUND_PERCENTAGE_FOR_BOX + 10));
		mailboxFactory->setSpawnFrequency(5);
		mailboxFactory->setSpeed(Vec2(-(Director::getInstance()->getWinSize().width * 10.0 / 800), 0));

		InteractiveObjectFactory* rocketFactory = InteractiveObjectFactory::create(OBJECT_ROCKET, director->getWinSize().height * 1.6 / 800, false, ROCKET_COLLISION_BITMASK, true, false, false);
		rocketFactory->setPositionInterval(Vec2(100, height));
		rocketFactory->setSpeed(Vec2(-(Director::getInstance()->getWinSize().width * 25.0 / 800), 0));
		rocketFactory->setSpawnFrequency(20);

		InteractiveObjectFactory* spikesFactory = InteractiveObjectFactory::create(OBJECT_SPIKES, director->getWinSize().height * 0.5 / 800, false, SPIKES_COLLISION_BITMASK, false, true, true);
		spikesFactory->setPositionInterval(Vec2(height / GROUND_PERCENTAGE_FOR_BOX + 10, height / GROUND_PERCENTAGE_FOR_BOX + 10));
		spikesFactory->setSpawnFrequency(5);
		spikesFactory->setSpeed(Vec2(-(Director::getInstance()->getWinSize().width * 10.0 / 800), 0));


		secondLevelLayer->setBackground(bckSecondLevel);
		secondLevelLayer->setPlayer(hero);
		secondLevelLayer->setBoss(boss);
		secondLevelLayer->setDistanceToBoss(100);
		secondLevelLayer->addObjectFactory(mailboxFactory);
		secondLevelLayer->addObjectFactory(rocketFactory);
		secondLevelLayer->addObjectFactory(spikesFactory);

		//Create Scene
		GameLevel* firstLevel = GameLevel::create(secondLevelLayer);

		return firstLevel;
	}
	if (levelIndex == 3)
	{
		Director* director = Director::getInstance();

		// Create a new GameLayer
		GameLayer* thirdLevelLayer = GameLayer::create();

		// Create a background
		ParallaxBackground* bckThirdLevel = new ParallaxBackground();

		float height = director->getWinSize().height;
		float width = director->getWinSize().width;

		// Create animations and bullets
		bckThirdLevel->addImage("night.png", Vec2(width / 2, height / 1.3), Vec2(0.05, 0));
		bckThirdLevel->addImage("city.png", Vec2(width / 2, height / 1.6), Vec2(0.3, 0));
		bckThirdLevel->addImage("street.png", Vec2(width / 2, height / 2.6), Vec2(1.0, 0), true);
		bckThirdLevel->scheduleUpdate();

		// Create music
		//CocosDenshion::SimpleAudioEngine* audioEngine = CocosDenshion::SimpleAudioEngine::getInstance();
		//audioEngine->playBackgroundMusic("darude.mp3", true);

		// Create player
		Player* hero = Player::create();
		hero->setPosition(Vec2(width / 2, 130));
		hero->setTag(PLAYER_TAG);

		// Create boss
		Boss* boss = Boss::create(OBJECT_THIRDBOSS);

		BossCannon* cannon1 = BossCannon::create(OBJECT_THIRDBOSS_CANNON_1, OBJECT_THIRDBOSS_CANNON_1_D, OBJECT_BOSSBULLET_BOMB);
		cannon1->setPosition(Vec2(70, 100));
		cannon1->setFireMethod(1, 10, 50);

		BossCannon* cannon2 = BossCannon::create(OBJECT_THIRDBOSS_CANNON_2, OBJECT_THIRDBOSS_CANNON_2_D, OBJECT_BOSSBULLET_RASENGAN);
		cannon2->setPosition(Vec2(50, 50));
		cannon2->setFireMethod(2, 10, 50);


		boss->addCannon(1, cannon1);
		boss->addCannon(2, cannon2);

		// Create Interactive object factory
		InteractiveObjectFactory* mailboxFactory = InteractiveObjectFactory::create(OBJECT_MAILBOX, director->getWinSize().height * 1.6 / 800, false, MAILBOX_COLLISION_BITMASK, true, false, true);
		mailboxFactory->setPositionInterval(Vec2(height / GROUND_PERCENTAGE_FOR_BOX + 10, height / GROUND_PERCENTAGE_FOR_BOX + 10));
		mailboxFactory->setSpawnFrequency(5);
		mailboxFactory->setSpeed(Vec2(-(Director::getInstance()->getWinSize().width * 10.0 / 800), 0));

		InteractiveObjectFactory* rocketFactory = InteractiveObjectFactory::create(OBJECT_ROCKET, director->getWinSize().height * 1.6 / 800, false, ROCKET_COLLISION_BITMASK, true, false, false);
		rocketFactory->setPositionInterval(Vec2(100, height));
		rocketFactory->setSpeed(Vec2(-(Director::getInstance()->getWinSize().width * 25.0 / 800), 0));
		rocketFactory->setSpawnFrequency(20);

		InteractiveObjectFactory* spikesFactory = InteractiveObjectFactory::create(OBJECT_SPIKES, director->getWinSize().height * 0.5 / 800, false, SPIKES_COLLISION_BITMASK, false, true, true);
		spikesFactory->setPositionInterval(Vec2(height / GROUND_PERCENTAGE_FOR_BOX + 10, height / GROUND_PERCENTAGE_FOR_BOX + 10));
		spikesFactory->setSpawnFrequency(5);
		spikesFactory->setSpeed(Vec2(-(Director::getInstance()->getWinSize().width * 10.0 / 800), 0));


		thirdLevelLayer->setBackground(bckThirdLevel);
		thirdLevelLayer->setPlayer(hero);
		thirdLevelLayer->setBoss(boss);
		thirdLevelLayer->setDistanceToBoss(100);
		thirdLevelLayer->addObjectFactory(mailboxFactory);
		thirdLevelLayer->addObjectFactory(rocketFactory);
		thirdLevelLayer->addObjectFactory(spikesFactory);

		//Create Scene
		GameLevel* firstLevel = GameLevel::create(thirdLevelLayer);

		return firstLevel;
	}

	return nullptr;
}


Vector<Scene*> SceneManager::mainStack;
