#pragma once
#include "cocos2d.h"
#include "InteractiveObject.h"
class GameLayer;

USING_NS_CC;
using namespace std;

class InteractiveObjectFactory
{
public:
	static InteractiveObjectFactory* create(int resourceIndex, float scaleFactor ,bool isAnimated, int maksValue, bool canBeFiredAt = false, bool canHitPlayer = false, bool gravityAffected = true);
	void setSpeed(Vec2 speed);
	void setSpawnFrequency(int frequency);
	void setGravityAffected(bool gravityAffected);
	void setPositionInterval(Vec2 interval);
	void setIsAnimated(bool isAnimated);
	void setParent(GameLayer* parent);
	void setCanBeFiredAt(bool canBeFiredAt);
	void setCanHitPlayer(bool canHitPlayer);
	void setResource(int resource);
	void createObject();


private:
	int resourceIndex;
	int maskValue;
	bool isAnimated;
	bool canBeFiredAt;
	bool canHitPlayer;
	bool gravityAffected;
	
	Vec2 speed;
	Vec2 spawnInterval;

	GameLayer* parent;
	int frequency;
	float scaleFactor;
	~InteractiveObjectFactory();
	InteractiveObjectFactory();
};
