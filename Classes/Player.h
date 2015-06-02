#pragma once

#include "cocos2d.h"
#include <string>
#include "Weapon.h"
USING_NS_CC;

using namespace std;

class Player : public Sprite
{
public:

	enum Action
	{
		JUMP_START = 0, JUMPING = 1, DOUBLE_JUMPING = 2, SLIDING = 3, RUNNING = 4, WALKING = 5
	};

	Player();

	~Player();
	void setBossMode(bool b);
	static Player* create();

	void initOptions();

	virtual void update(float delta) override;
	bool isKeyPressed(EventKeyboard::KeyCode code);

	void fire();
	void jump();
	void slide();
	void doubleJump();
	void isHit();
	void setDistanceTravelled(long long dist);
	long long getDistanceTravelled();

	// UI
	int getScore();
	int getHealth();
	void setScore(int score);
	void addScore(int toAdd);
private:
	std::map < cocos2d::EventKeyboard::KeyCode,
		std::chrono::high_resolution_clock::time_point > keys;
	Weapon* weapon;
	void callback_WorUp();
	void setWeapon(Weapon* weapon);
	Action currentAction = Action::RUNNING;
	long long distanceTravelled;
	bool bossMode = false;
	
	int score = 0;
	int HP = 100;
};
