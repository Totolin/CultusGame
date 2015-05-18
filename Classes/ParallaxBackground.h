#pragma once
#include <string>
#include<vector>
using namespace std;

#include "cocos2d.h"
USING_NS_CC;

class ParallaxBackground:public Layer
{
public:
	ParallaxBackground();
	void addImage(string imageName,Vec2 imagePosition, Vec2 imageVelocity);
	void update(float delta) override;
	void slowlyStop();
private:
	int zOrder;

};
