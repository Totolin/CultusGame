#pragma once

#include "cocos2d.h"

USING_NS_CC;

using namespace std;

class BossCannon : public Sprite
{
public:
	enum FireState{
		DONT_FIRE = 0,
		FIRE= 1,
		DESTROYED = 2,
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
	void nextState();
	void updatePlayerPosition(Vec2 position);
	void setFireMethod(int fireMethod,int numberOfBullets, int pauseTime);
private:

	void fire();
	int HP;
	int destroyedSpriteIndex;
	int cannonProjectile;
	int currentFireState;
	int framesPassed;
	int cooldown;
	Vec2 playerPosition;

	// Firing properties
	int fireMethod;
	int numberOfBullets;
	int pauseTime;
	int numberOfFiredBullets;
};

