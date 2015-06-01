#pragma once
#include "Boss.h"
#include "BossCannon.h"
class FirstBoss : public Boss
{
public:
	FirstBoss();
	~FirstBoss();

	virtual void update(float delta) override;
	static FirstBoss* create(int spriteIndex);
	void setPhysics();
	void addCannon_1(int cannonIndexAlive, int cannonIndexDestroyed, int cannonProjectile);
	virtual void moveIn(Vec2 position);

private:
	Vec2 positionToMove;
	BossCannon* cannon1;
};

