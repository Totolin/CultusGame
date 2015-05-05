#pragma once
#include "cocos2d.h"
#include "InteractiveObject.h"

USING_NS_CC;
using namespace std;

class InteractiveObjectFactory
{
public:
	static InteractiveObjectFactory* create(int resourceIndex, bool isAnimated, bool canBeFiredAt = false, bool canHitPlayer = false);
	void setSpeed(Vec2 speed);
	void setSpawnFrequency(int frequency);
	void setPositionInterval(Vec2 interval);
	void setIsAnimated(bool isAnimated);

	void setCanBeFiredAt(bool canBeFiredAt);
	void setCanHitPlayer(bool canHitPlayer);
	void setResource(int resource);
	void createObject();
	//TODO: remove obsolete occurrences

private:
	int resourceIndex;

	bool isAnimated;
	bool canBeFiredAt;
	bool canHitPlayer;

	Vec2 speed;
	Vec2 spawnInterval;

	int frequency;

	~InteractiveObjectFactory();
	InteractiveObjectFactory();
	vector<InteractiveObject*> objects;
};
