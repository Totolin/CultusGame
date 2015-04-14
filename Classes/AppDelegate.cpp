#include "AppDelegate.h"
#include "HelloWorldScene.h"
#include "GameLevel.h"
#include "ParallaxBackground.h"

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
		glview->setFrameSize(1000, 700);
		director->setOpenGLView(glview);
	}

	auto scene = Scene::create();
	ParallaxBackground* bck = new ParallaxBackground();
	
	int height = director->getWinSize().height;
	int width = director->getWinSize().width;

	//bck->addImage("image4.png", Vec2(width / 2, 400), Vec2(0.5, 0));
	bck->addImage("image2.png", Vec2(width / 2, 300), Vec2(1.2, 0));
	//bck->addImage("image3.png", Vec2(width / 2, 200), Vec2(1.9, 0));
	bck->initialize();
	scene->addChild(bck);
	director->runWithScene(scene);

	return true;
}

void AppDelegate::applicationDidEnterBackground() {
}

void AppDelegate::applicationWillEnterForeground() {
}