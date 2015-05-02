#pragma once
#include "cocos2d.h"
#include "Bullet.h"
#include "GameValues.h"

USING_NS_CC;
using namespace std;
class Weapon
{
public:
	Weapon();
	static Weapon* create();
	void fireBullet(float X, float Y);
	~Weapon();
	void nextLevel();
	void update();
private:
	vector<Bullet*> bullets;
	int bulletLevel = PLAYER_BULLET_LVL_1;
};
