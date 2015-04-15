#pragma once

#include "cocos2d.h"
#include <string>
USING_NS_CC;

using namespace std;

class Player : public Sprite
{
public:
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
private:
	static std::map < cocos2d::EventKeyboard::KeyCode,
		std::chrono::high_resolution_clock::time_point > keys;
};
