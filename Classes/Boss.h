#pragma once
#include "cocos2d.h"
#include <string>
USING_NS_CC;

using namespace std;

class Boss : public Sprite
{
public:

	enum State
	{
		AWAITING = -1,

		MOVE_IN = 0,
		GO_TO_MODE_1 =1,

		FIRST_MODE=2,
		GO_TO_MODE_2 = 3,

		SECOND = 4,
		GO_TO_MODE_3 = 5,

		THIRD = 6,
		GO_TO_DIE = 7,
		DYING = 8
	};

	Boss();
	~Boss();
	virtual void update(float delta) override;
	void setState(State state);
	void nextState();
	void moveX(int pixelsToMove);
	void moveY(int pixelsToMove);
	virtual void moveIn(Vec2 position);
protected:
	int currentState;
};

