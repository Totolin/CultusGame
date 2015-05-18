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
	//void setPosition(Vec2 position);
	void initOptions();

	virtual void update(float delta) override;
	bool isKeyPressed(EventKeyboard::KeyCode code);
	void moveX(int pixelsToMove);
	void moveY(int pixelsToMove);

	void fire();
	void jump();
	void slide();
	void doubleJump();
	void setGroundLevel(float groundLevel);
	void setDistanceTravelled(long long dist);
	long long getDistanceTravelled();
	int getScore();
	void setScore(int score);
private:
	std::map < cocos2d::EventKeyboard::KeyCode,
		std::chrono::high_resolution_clock::time_point > keys;
	float groundLevel;
	Weapon* weapon;
	void callback_WorUp();
	void setWeapon(Weapon* weapon);
	bool onScreenLeft();
	bool onScreenRight();
	Action currentAction = Action::RUNNING;
	long long distanceTravelled;
	bool bossMode = false;
	int score = 0;
};
