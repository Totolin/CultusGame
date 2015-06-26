#pragma once
#include "Boss.h"
#include "BossCannon.h"
#include <vector>
#define STATE_LEFT_SHIFT -2
class Boss : public Sprite
{
	enum State
	{
		AWAITING = -1,

		MOVE_IN = 0,
		GO_TO_MODE_1 = 1,

		FIRST_MODE = 2,
		GO_TO_MODE_2 = 3,

		SECOND_MODE = 4,
		GO_TO_MODE_3 = 5,

		THIRD_MODE = 6,
		GO_TO_DIE = 7,
		DYING = 8
	};

public:
	Boss();
	~Boss();

	bool smallExplosions();
	void bigExplosion();
	virtual void update(float delta) override;
	bool isFlying();
	static Boss* create(int spriteIndex, bool flying = false);
	void setPhysics();
	void addCannon(int stateOfParent, BossCannon* cannon);
	void moveIn(Vec2 position);
	void updatePlayerPosition(Vec2 playerPosition);
	void nextState();
	void moveX(int pixelsToMove);
	void moveY(int pixelsToMove);
	void setState(State state);

private:
	Vec2 positionToMove;
	int currentState;
	void changeCannons();
	bool checkCannonsStatus();
	int numberOfDestroyedCannons;
	int cannonsArrayStateIndex;
	int framesForExplosions;
	// We will consider a maximum number of states to be 3. Meaning that only
	// 3 arrays of cannons are necessary.
	Vector<BossCannon*> cannons[3];
	vector<Vec2> explosionPositions;
	int explosionIndex;
	bool flying;
};

