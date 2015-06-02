#pragma once
using namespace std;

#include "cocos2d.h"
USING_NS_CC;

class InteractiveObject : public Sprite
{
public:
	static InteractiveObject* create(int resourceIndex, int maskValue, bool isAnimated = false);
	void setSpeed(Vec2 speed);

	void setCanBeFiredAt(bool canBeFiredAt);
	void setCanHitPlayer(bool canHitPlayer);
	
	bool getCanBeFireAt();
	bool getCanHitPlayer();
	void isHit();
	virtual void update(float delta) override;
	void setGravityAffected(bool dynamic);
	bool isGravityAffected();
	Vec2 getSpeed();
private:
	bool canBeFiredAt;
	bool canHitPlayer;

	Vec2 speed;
	bool gravityAffected;
	bool hasBeenHit;
	InteractiveObject();
	~InteractiveObject();
};
