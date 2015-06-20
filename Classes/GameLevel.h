#pragma once

#include "cocos2d.h"
#include "GameLayer.h"
#include "PauseMenu.h"

USING_NS_CC;
using namespace std;
using namespace ui;

class GameLevel : public Scene
{
public:
	static GameLevel* create(GameLayer* layer, PauseMenu* menu);

private:
	GameLevel();
	~GameLevel();
	static GameLevel* createWithPhysics();
	GameLayer* gameLayer;
	PauseMenu* pauseMenu;
	bool isPaused;
};