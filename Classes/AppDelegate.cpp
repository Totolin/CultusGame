#include "AppDelegate.h"
#include "HelloWorldScene.h"
#include "GameLevel.h"

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
		glview->setFrameSize(1000, 1000);
		director->setOpenGLView(glview);
	}

	// TODO : Test
	GameLevel level;
	ParallaxBackground* background = new ParallaxBackground();
	background->addBackground("image3.png", Vec2(1.2f, 1.0f), Vec2::ZERO, Vec2(100, 100));
	background->addBackground("image2.png", Vec2(2.2f, 1.0f), Vec2(100, 100), Vec2(300, 300));
	background->addBackground("image1.png", Vec2(3.2f, 1.0f), Vec2(300, 300), Vec2(500, 500));

	level.setBackground(background);
	director->runWithScene(level.createScene());

	/*auto scene = HelloWorldScene::createScene();
	director->runWithScene(scene);*/

	return true;
}

void AppDelegate::applicationDidEnterBackground() {
}

void AppDelegate::applicationWillEnterForeground() {
}