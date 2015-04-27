#pragma once

#include "cocos2d.h"
#include "Boss.h"
#include "ParallaxBackground.h"
#include "Player.h"
#include "SimpleAudioEngine.h"
#include "InteractiveObjectFactory.h"
#include <vector>
#include <string>

USING_NS_CC;
using namespace std;

class GameLevel : public Ref
{
public:
	GameLevel();
	~GameLevel();

	Scene* createScene();
	void setBoss(Boss* levelBoss);
	void setBackground(ParallaxBackground* levelBackground);
	void setPlayer(Player* mainCharacter);
	void setAudioEngine(CocosDenshion::SimpleAudioEngine* audioEngine);
	void setMusic(string backgroundMusic);
	void addObjectFactory(InteractiveObjectFactory* objectFactory);

private:
	Boss* levelBoss;
	Player* mainCharacter;
	ParallaxBackground* levelBackground;
	vector<InteractiveObjectFactory*> objectFactories;
	CocosDenshion::SimpleAudioEngine* audioEngine;
	string backgroundMusic;
};
