#pragma once

#include "cocos2d.h"

USING_NS_CC;

using namespace std;

class BossCannon : public Sprite
{
public:
	enum FireState{
		DONT_FIRE = 0,
		METHOD1 = 1,
		METHOD2 = 2,
		METHOD3 = 3
	};

	BossCannon();
	~BossCannon();
	virtual void update(float delta) override;
	static BossCannon* create(int spriteIndex, int destroyedSpriteIndex, int cannonProjectile);

	void destroyCannon();
	int getHP();
	void reduceHP(int amount);
	void setPhysics();
	bool isDestroyed();
	//void setFireMethod1(int numberOfBullets, int bulletInterval, int timeToTravel, Vector<Vec2> positions, int pauseTime);
private:

	void fireMethod1();
	int HP;
	int destroyedSpriteIndex;
	int cannonProjectile;
	bool destroyed;
	int currentFireState;
	int framesPassed;
};

