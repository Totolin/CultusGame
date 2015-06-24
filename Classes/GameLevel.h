#pragma once

#include "cocos2d.h"
#include "GameLayer.h"

USING_NS_CC;
using namespace std;
using namespace ui;

class GameLevel : public Scene
{
public:
	static GameLevel* create(GameLayer* layer);
	void resumeButtonCallback();
	void escapeButtonCallback();
	void gameOver();
	GameLayer* getGameLayer();
private:
	GameLevel();
	~GameLevel();
	static GameLevel* createWithPhysics();

	void initOptions();
	GameLayer* gameLayer;
	bool isPaused;
};