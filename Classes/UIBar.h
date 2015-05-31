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
	void addPercent(float percentage);
	void substractPercent(float percentage);
	float getPercent();
	
	void resetScore();
	void addScore(int score);
	int getScore();
	void setScore(int score);
private:
	Label* nameLabel;
	Label* scoreLabel;
	LoadingBar* fillingBar;
	int score;
};
