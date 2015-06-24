#pragma once
#include "cocos2d.h"
#include "GameLevel.h"

USING_NS_CC;
using namespace std;

class PauseMenu : public Layer
{
public:
	enum MenuType { PAUSE, DEAD };

	static PauseMenu* create(MenuType menuType);
private:
	PauseMenu();
	~PauseMenu();
	void resumeButtonCallback();
};

