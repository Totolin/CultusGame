#include "AppDelegate.h"
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
		glview->setFrameSize(800, 600);
		director->setOpenGLView(glview);
	}

	director->setAnimationInterval(1.0 / 30);

	// Create a new GameLevel
	auto firstLevel = GameLevel::create();

	// Create a background
	ParallaxBackground* bck = new ParallaxBackground();

	int height = director->getWinSize().height;
	int width = director->getWinSize().width;

	bck->addImage("night.png", Vec2(width / 2, 400), Vec2(0.05, 0));
	bck->addImage("city.png", Vec2(width / 2, 348), Vec2(0.3, 0));
	bck->addImage("street.png", Vec2(width / 2, 89), Vec2(1.9, 0));
	bck->scheduleUpdate();

	// Create animations and bullets
	ResourceLoader resLoader = ResourceLoader::getInstance();
	resLoader.addAnimation("runner", 8, PLAYER_ANIMATION_RUNNING);
	resLoader.addBulletFile("bullet.png", PLAYER_BULLET_LVL_1);
	resLoader.addImageFile("mailbox.png", OBJECT_MAILBOX);

	// Create Interactive object factory
	InteractiveObjectFactory* mailboxFactory = InteractiveObjectFactory::create(OBJECT_MAILBOX, false, true, false);
	mailboxFactory->setPositionInterval(Vec2(0, 100));

	// Create player
	Player* hero = Player::create();
	hero->setPosition(Vec2(width / 2, 130));
	hero->setGroundLevel(130);
	hero->setTag(PLAYER_TAG);

	// Create music
	CocosDenshion::SimpleAudioEngine* audioEngine = CocosDenshion::SimpleAudioEngine::getInstance();
	//audioEngine->playBackgroundMusic("darude.mp3", true);

	//firstLevel->setBackground(bck);
	firstLevel->setPlayer(hero);
	firstLevel->addObjectFactory(mailboxFactory);
	firstLevel->setDistanceToBoss(200);

	auto startScene = IntermediaryScene::create(IntermediaryScene::MENU);
	startScene->setBackground(bck);

	auto dummy = DummyPlayer::create();
	dummy->setPosition(Vec2(width / 2, 130));
	startScene->setPlayer(dummy);

	Label* playButtonLabel = Label::createWithTTF("Play", "font.ttf", 35);
	MenuItem* playButton = MenuItemLabel::create(playButtonLabel, [&](Ref* sender){log("Clicked play"); });

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