#pragma once

#include "cocos2d.h"
#include <string>
#include "Weapon.h"
USING_NS_CC;

using namespace std;

class DummyPlayer : public Sprite
{
public:

	DummyPlayer();
	~DummyPlayer();
	static DummyPlayer* create();

	virtual void update(float delta) override;
};
