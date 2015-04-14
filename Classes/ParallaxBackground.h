#pragma once
#include <string>

using namespace std;

#include "cocos2d.h"
USING_NS_CC;

class ParallaxBackground
{
public:
	ParallaxBackground();
	~ParallaxBackground();

	void addBackground(string imageName, Vec2 imageRatio, Vec2 imageOffset, Vec2 imagePosition);
	ParallaxNode* createParallaxBackground();

private:
	int currentPositioning;
	ParallaxNode* background;
};
