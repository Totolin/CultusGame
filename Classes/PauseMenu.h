#pragma once
#include "cocos2d.h"
#include "GameLevel.h"

USING_NS_CC;
using namespace std;

class PauseMenu : public Layer
{
public:
	static PauseMenu* create(GameLevel* parentRefference);
private:
	PauseMenu();
	~PauseMenu();
	void resumeButtonCallback();
};

