#pragma once
#include<string>
#include "cocos2d.h"

USING_NS_CC;
using namespace std;
class ResourceLoader
{
public:
	static ResourceLoader& getInstance();
	static Vector<SpriteFrame*> getAnimation(int key);
	static void addAnimation(string animationName, int numberOfFrames, int key);
private:
	ResourceLoader();
	static map<int, Vector<SpriteFrame*>> animations;
};
