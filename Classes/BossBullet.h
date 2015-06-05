#pragma once

#include "cocos2d.h"
USING_NS_CC;
using namespace std;

class BossBullet :public Sprite
{
public:
	static BossBullet* create(int bulletFileIndex);
	virtual void update(float delta) override;
	void isHit();
	void setExplodeOnGround(bool b);
	bool getExplodeOnGround();
private:
	bool hit;
	bool explodeOnGround;
};