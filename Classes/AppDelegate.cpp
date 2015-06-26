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
		glview = GLViewImpl::create("CULTUS");
		glview->setFrameSize(1366, 780);
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
	resLoader.addImageFile("runner_dead.png", PLAYER_ANIMATION_DEAD);
	resLoader.addImageFile("firstboss_cannon_3.png", OBJECT_FIRSTBOSS_CANNON_3);
	resLoader.addImageFile("firstboss_cannon_3_d.png", OBJECT_FIRSTBOSS_CANNON_3_D);
	resLoader.addImageFile("firstboss_cannon_3_pr.png", OBJECT_BOSSBULLET_BALL);


	director->runWithScene(SceneManager::getInstance().generateLevel(0));

	return true;
}

void AppDelegate::applicationDidEnterBackground() {
	Director::getInstance()->stopAnimation();
}

void AppDelegate::applicationWillEnterForeground() {
	Director::getInstance()->startAnimation();
} 