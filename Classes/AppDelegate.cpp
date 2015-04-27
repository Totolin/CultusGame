#include "AppDelegate.h"
#include "HelloWorldScene.h"
#include "GameLevel.h"
#include "ParallaxBackground.h"
#include "ResourceLoader.h"
#include "GameValues.h"

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

	auto scene = Scene::create();
	ParallaxBackground* bck = new ParallaxBackground();

	int height = director->getWinSize().height;
	int width = director->getWinSize().width;

	bck->addImage("night.png", Vec2(width / 2, 400), Vec2(0.05, 0));
	bck->addImage("city.png", Vec2(width / 2, 348), Vec2(0.3, 0));
	bck->addImage("street.png", Vec2(width / 2, 89), Vec2(1.9, 0));
	bck->scheduleUpdate();
	scene->addChild(bck);

	ResourceLoader resLoader = ResourceLoader::getInstance();
	resLoader.addAnimation("runner", 8, PLAYER_ANIMATION_RUNNING);

	Player* hero = Player::create();
	hero->setPosition(Vec2(width / 2, 130));
	hero->setGroundLevel(130);
	scene->addChild(hero);

	director->runWithScene(scene);
	return true;
}

void AppDelegate::applicationDidEnterBackground() {
	Director::getInstance()->stopAnimation();
}

void AppDelegate::applicationWillEnterForeground() {
	Director::getInstance()->startAnimation();
}