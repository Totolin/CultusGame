#pragma once

#include "cocos2d.h"
USING_NS_CC;
using namespace std;

class Bullet :public Sprite
{
public:
	static Bullet* create(int bulletFileIndex);
	virtual void update(float delta) override;
	void isHit();
private:
	bool hit;
};