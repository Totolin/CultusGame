#include "AppDelegate.h"
#include "TestScene.h"
#include "HelloWorldScene.h"
#include "GameLevel.h"
#include "ParallaxBackground.h"
#include "ResourceLoader.h"
#include "GameValues.h"
#include "IntermediaryScene.h"
#include <iostream>
#include "FirstBoss.h"
#include "BossCannon.h"

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
	resLoader.addImageFile("firstboss_cannon_1_pr.png", OBJECT_FIRSTBOSS_CANNON_1_PR);

	// Create a new GameLevel
	auto firstLevel = GameLevel::create();

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
	FirstBoss* boss = FirstBoss::create(OBJECT_FIRSTBOSS);
	boss->addCannon_1(OBJECT_FIRSTBOSS_CANNON_1, OBJECT_FIRSTBOSS_CANNON_1_D, OBJECT_FIRSTBOSS_CANNON_1_PR);

	// Create Interactive object factory
	InteractiveObjectFactory* mailboxFactory = InteractiveObjectFactory::create(OBJECT_MAILBOX,false, MAILBOX_COLLISION_BITMASK,true, false, true);
	mailboxFactory->setPositionInterval(Vec2(height / GROUND_PERCENTAGE_FOR_BOX + 30, height / GROUND_PERCENTAGE_FOR_BOX + 100));

	InteractiveObjectFactory* rocketFactory = InteractiveObjectFactory::create(OBJECT_ROCKET, false,ROCKET_COLLISION_BITMASK,true, false, false);
	rocketFactory->setPositionInterval(Vec2(340, 700));

	firstLevel->setBackground(bckFirstLevel);
	firstLevel->setPlayer(hero);
	firstLevel->setBoss(boss);
	firstLevel->setDistanceToBoss(500);
	firstLevel->addObjectFactory(mailboxFactory);
	firstLevel->addObjectFactory(rocketFactory);

	// Add first level to stack
	Director::getInstance()->pushScene(firstLevel);

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
	Director::getInstance()->popScene();
}