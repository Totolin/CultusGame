#pragma once

#include "cocos2d.h"

USING_NS_CC;

using namespace std;

class Bullet :public Sprite
{
public:
	static Bullet* create();
	void moveX(int pixelsToMove);
	virtual void update(float delta) override;
};