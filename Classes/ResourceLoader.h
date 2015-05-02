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
	static void addBulletFile(string bulletFile, int index);
	static std::string getBulletFile(int index);

private:
	ResourceLoader();
	static map<int, Vector<SpriteFrame*>> animations;
	static vector<string> bulletFiles;
};
