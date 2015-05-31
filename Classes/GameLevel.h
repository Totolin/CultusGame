#pragma once

#include "cocos2d.h"
#include "Boss.h"
#include "ParallaxBackground.h"
#include "Player.h"
#include "SimpleAudioEngine.h"
#include "InteractiveObjectFactory.h"
#include <vector>
#include <string>
#include <cocos2d/cocos/ui/UILoadingBar.h>
#include "UIBar.h"

USING_NS_CC;
using namespace std;
using namespace ui;

class GameLevel : public Scene
{
public:
	GameLevel();
	~GameLevel();

	static GameLevel* create();
	static GameLevel* createWithPhysics();

	void setBoss(Boss* levelBoss);
	void setBackground(ParallaxBackground* levelBackground);
	void setPlayer(Player* mainCharacter);
	void setDistanceToBoss(long long distance);
	void setAudioEngine(CocosDenshion::SimpleAudioEngine* audioEngine);
	void setMusic(string backgroundMusic);
	void addObjectFactory(InteractiveObjectFactory* objectFactory);
	virtual void update(float delta) override;
	void updateUI();
private:
	bool onContactBegin(PhysicsContact &contact);

	Boss* levelBoss;
	Player* mainCharacter;
	ParallaxBackground* levelBackground;
	vector<InteractiveObjectFactory*> objectFactories;
	CocosDenshion::SimpleAudioEngine* audioEngine;
	string backgroundMusic;
	long long distance;
	UIBar* statusBar;
};
