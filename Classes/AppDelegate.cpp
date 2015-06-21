#include "AppDelegate.h"
#include "TestScene.h"
#include "GameLayer.h"
#include "ParallaxBackground.h"
#include "ResourceLoader.h"
#include "GameValues.h"
#include "IntermediaryScene.h"
#include <iostream>
#include "Boss.h"
#include "BossCannon.h"
#include "GameLevel.h"
#include "SceneManager.h"

USING_NS_CC;

AppDelegate::AppDelegate() {
}

AppDelegate::~AppDelegate()
{
}

bool AppDelegate::applicationDidFinishLaunching() {
	// Set director and create a screen using OpenGLView
	auto director = Director::getInstance();
	auto glview = director->getOpenGLView();
	if (!glview) {
		glview = GLViewImpl::create("Hello World");
		glview->setFrameSize(1200, 630);
		director->setOpenGLView(glview);
	}

	director->setAnimationInterval(1.0 / 30);

	// Create animations and bullets
	ResourceLoader resLoader = ResourceLoader::getInstance();
	resLoader.addAnimation("runner", 8, PLAYER_ANIMATION_RUNNING);
	resLoader.addBulletFile("bullet.png", PLAYER_BULLET_LVL_1);
	resLoader.addImageFile("mailbox.png", OBJECT_MAILBOX);
	resLoader.addImageFile("rocket.png", OBJECT_ROCKET);
	resLoader.addImageFile("firstboss.png", OBJECT_FIRSTBOSS);
	resLoader.addImageFile("firstboss_cannon_1.png", OBJECT_FIRSTBOSS_CANNON_1);
	resLoader.addImageFile("firstboss_cannon_1_d.png", OBJECT_FIRSTBOSS_CANNON_1_D);
	resLoader.addImageFile("firstboss_cannon_1_pr.png", OBJECT_BOSSBULLET_LASER);
	resLoader.addImageFile("spikes.png", OBJECT_SPIKES);
	resLoader.addImageFile("firstboss_cannon_2.png", OBJECT_FIRSTBOSS_CANNON_2);
	resLoader.addImageFile("firstboss_cannon_2_d.png", OBJECT_FIRSTBOSS_CANNON_2_D);
	resLoader.addImageFile("firstboss_cannon_2_pr.png", OBJECT_BOSSBULLET_SPIKEBALL);


	// Create a new GameLayer
	GameLayer* firstLevelLayer = GameLayer::create();

	// Create a background
	ParallaxBackground* bckFirstLevel = new ParallaxBackground();

	float height = director->getWinSize().height;
	float width = director->getWinSize().width;

	// Create animations and bullets
	bckFirstLevel->addImage("night.png", Vec2(width / 2,width / 2), Vec2(0.05, 0));
	bckFirstLevel->addImage("city.png", Vec2(width / 2, width / 2), Vec2(0.3, 0));
	bckFirstLevel->addImage("street.png", Vec2(width / 2,width / 4), Vec2(1.0, 0));
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

	boss->addCannon(1,cannon2);
	boss->addCannon(2,cannon1);

	// Create Interactive object factory
	InteractiveObjectFactory* mailboxFactory = InteractiveObjectFactory::create(OBJECT_MAILBOX,1,false, MAILBOX_COLLISION_BITMASK,true, false, true);
	mailboxFactory->setPositionInterval(Vec2(height / GROUND_PERCENTAGE_FOR_BOX, height / GROUND_PERCENTAGE_FOR_BOX + 100));
	mailboxFactory->setSpawnFrequency(8);

	InteractiveObjectFactory* rocketFactory = InteractiveObjectFactory::create(OBJECT_ROCKET,1, false,ROCKET_COLLISION_BITMASK,true, false, false);
	rocketFactory->setPositionInterval(Vec2(340, 700));
	rocketFactory->setSpeed(Vec2(-20, 0));
	rocketFactory->setSpawnFrequency(30);

	InteractiveObjectFactory* spikesFactory = InteractiveObjectFactory::create(OBJECT_SPIKES,0.5, false, SPIKES_COLLISION_BITMASK, false, true, true);
	spikesFactory->setPositionInterval(Vec2(height / GROUND_PERCENTAGE_FOR_BOX, height / GROUND_PERCENTAGE_FOR_BOX + 50));
	spikesFactory->setSpawnFrequency(5);

	firstLevelLayer->setBackground(bckFirstLevel);
	firstLevelLayer->setPlayer(hero);
	firstLevelLayer->setBoss(boss);
	firstLevelLayer->setDistanceToBoss(1000);
	firstLevelLayer->addObjectFactory(mailboxFactory);
	firstLevelLayer->addObjectFactory(rocketFactory);
	firstLevelLayer->addObjectFactory(spikesFactory);

	// Create Pause Menu

	//Create Scene
	GameLevel* firstLevel = GameLevel::create(firstLevelLayer);


	// Add first level to stack
	SceneManager::getInstance().addSceneToMainStack(firstLevel);

	// Create start scene
	ParallaxBackground* bckMenu = new ParallaxBackground();
	bckMenu->addImage("night.png", Vec2(width / 2, width / 2), Vec2(0.05, 0));
	bckMenu->addImage("city.png", Vec2(width / 2, width / 2), Vec2(0.3, 0));
	bckMenu->addImage("street.png", Vec2(width / 2, width / 4), Vec2(1.0, 0));
	bckMenu->scheduleUpdate();

	auto startScene = IntermediaryScene::create(IntermediaryScene::MENU);
	startScene->setBackground(bckMenu);

	// Create dummy player
	auto dummy = DummyPlayer::create();
	dummy->setPosition(Vec2(width / 2, 130));
	startScene->setPlayer(dummy);

	Label* playButtonLabel = Label::createWithTTF("Play", "font.ttf", 35);
	MenuItem* playButton = MenuItemLabel::create(playButtonLabel, [&](Ref* sender){playButtonCallback(); });

	Label* optionsButtonLabel = Label::createWithTTF("Options", "font.ttf", 35);
	MenuItem* optionsButton = MenuItemLabel::create(optionsButtonLabel);

	Label* exitButtonLabel = Label::createWithTTF("Exit", "font.ttf", 35);
	MenuItem* exitButton = MenuItemLabel::create(exitButtonLabel, [&](Ref* sender){Director::getInstance()->end(); });

	startScene->addMenuItem(playButton);
	startScene->addMenuItem(optionsButton);
	startScene->addMenuItem(exitButton);
	startScene->createMenu();

	director->runWithScene(startScene);

	return true;
}

void AppDelegate::applicationDidEnterBackground() {
	Director::getInstance()->stopAnimation();
}

void AppDelegate::applicationWillEnterForeground() {
	Director::getInstance()->startAnimation();
}

void AppDelegate::playButtonCallback()
{
	SceneManager::getInstance().fillStack();
}