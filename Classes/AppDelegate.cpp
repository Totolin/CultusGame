#include "AppDelegate.h"
#include "TestScene.h"
#include "HelloWorldScene.h"
#include "GameLevel.h"
#include "ParallaxBackground.h"
#include "ResourceLoader.h"
#include "GameValues.h"
#include "IntermediaryScene.h"
#include <iostream>

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
		glview->setFrameSize(1600, 800);
		director->setOpenGLView(glview);
	}

	director->setAnimationInterval(1.0 / 30);

	// Create animations and bullets
	ResourceLoader resLoader = ResourceLoader::getInstance();
	resLoader.addAnimation("runner", 8, PLAYER_ANIMATION_RUNNING);
	resLoader.addBulletFile("bullet.png", PLAYER_BULLET_LVL_1);
	resLoader.addImageFile("mailbox.png", OBJECT_MAILBOX);
	resLoader.addImageFile("rocket.png", OBJECT_ROCKET);

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

	// Create Interactive object factory
	InteractiveObjectFactory* mailboxFactory = InteractiveObjectFactory::create(OBJECT_MAILBOX,false, MAILBOX_COLLISION_BITMASK,true, false, true);
	mailboxFactory->setPositionInterval(Vec2(height / GROUND_PERCENTAGE_FOR_BOX + 10, height / GROUND_PERCENTAGE_FOR_BOX + 100));

	InteractiveObjectFactory* rocketFactory = InteractiveObjectFactory::create(OBJECT_ROCKET, false,ROCKET_COLLISION_BITMASK,true, false, false);
	rocketFactory->setPositionInterval(Vec2(200, 700));

	firstLevel->setBackground(bckFirstLevel);
	firstLevel->setPlayer(hero);
	firstLevel->setDistanceToBoss(200);
	firstLevel->addObjectFactory(mailboxFactory);
	firstLevel->addObjectFactory(rocketFactory);

	director->runWithScene(firstLevel);

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