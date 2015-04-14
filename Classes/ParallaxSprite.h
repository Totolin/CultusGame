#pragma once
#include "cocos2d.h"
#include <string>
using namespace std;
USING_NS_CC;

class ParallaxSprite : public Sprite
{
public:
	static ParallaxSprite* create(string imgName);
	void setVelocityFactor(Vec2& velocity);
	Vec2& getVelocityFactor();
private:
	Vec2 velocity;
};

