#pragma once
using namespace std;

#include "cocos2d.h"
USING_NS_CC;

class InteractiveObject : public Sprite
{
public:
	static InteractiveObject* create(int resourceIndex, bool isAnimated = false);
	void setSpeed(Vec2 speed);

	void setCanBeFiredAt(bool canBeFiredAt);
	void setCanHitPlayer(bool canHitPlayer);

	virtual void update(float delta) override;

private:
	bool canBeFiredAt;
	bool canHitPlayer;

	Vec2 speed;

	InteractiveObject();
	~InteractiveObject();
};
