#pragma once
#include "cocos2d.h"
#include <string>
using namespace std;
USING_NS_CC;

class ParallaxSprite : public Sprite
{
public:
	static ParallaxSprite* create(string imgName);
	void setVelocity(Vec2& velocity);
	Vec2& getVelocity();
private:
	Vec2 velocity;
};

