#pragma once

#include "cocos2d.h"
#include <string>
USING_NS_CC;

using namespace std;

class Player : public Sprite
{
public:

	enum Action
	{
		JUMP_START = 0, JUMPING = 1, DOUBLE_JUMPING = 2, SLIDING = 3, RUNNING = 4, BOSSING = 5
	};

	Player();

	~Player();

	static Player* create(string png, string plist);
	//void setPosition(Vec2 position);
	void initOptions();

	virtual void update(float delta) override;
	bool isKeyPressed(EventKeyboard::KeyCode code);
	void moveX(int pixelsToMove);
	void moveY(int pixelsToMove);

	void jump();
	void slide();
	void doubleJump();
	void setGroundLevel(float groundLevel);
private:
	std::map < cocos2d::EventKeyboard::KeyCode,
		std::chrono::high_resolution_clock::time_point > keys;
	float groundLevel;
	void callback_WorUp();
	Action currentAction = Action::RUNNING;

	RepeatForever* runningAction;
	Vector<SpriteFrame*> animationFrames;
};
