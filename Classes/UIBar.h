#pragma once
#include "cocos2d.h"
#include <cocos2d/cocos/ui/UILoadingBar.h>

USING_NS_CC;
using namespace std;
using namespace ui;
class UIBar: public Sprite
{
public:
	
	static UIBar* create(string name);

	void setPercent(float percentage);
	void setScore(int score);
private:
	Label* nameLabel;
	Label* scoreLabel;
	LoadingBar* fillingBar;
};
